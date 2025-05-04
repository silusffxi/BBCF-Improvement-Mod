#include <atomic>
#include <memory>
#include <mutex>
#include "../platform.h"
#include <MinHook.h>
#include <detours.h>
#include "../logger.h"
#include "../utilities/hook_tools.hpp"
#include "d3d.h"
#include "../D3D9EXWrapper/ID3D9EXWrapper.h"
#include "../D3D9EXWrapper/ID3DXWrapper_Effect.h"
#include "../D3D9EXWrapper/ID3D9Wrapper_Sprite.h"
#include "d3d_hooks.h"

namespace
{
    std::atomic_bool detours_installed = false;
    std::mutex       detours_mutex;

    HMODULE module_d3d9     = nullptr;
    HMODULE module_d3dx9_43 = nullptr;

    LPVOID base_direct_3d_create9_ex = nullptr;
    LPVOID base_d3d_create_effect    = nullptr;
    LPVOID base_d3d_create_sprite    = nullptr;

    func_Direct3DCreate9Ex orig_direct_3d_create9_ex = nullptr;
    func_D3DCreateEffect   orig_d3d_create_effect    = nullptr;
    func_D3DCreateSprite   orig_d3d_create_sprite    = nullptr;

    std::unique_ptr<Direct3D9ExWrapper> d3d9_ex_wrapper = nullptr;
    std::unique_ptr<ID3DXEffectWrapper> d3d9x_effect_wrapper = nullptr;
    std::unique_ptr<ID3DXSpriteWrapper> d3d9x_sprite_wrapper = nullptr;

    /**
    *@brief Creates an @c IDirect3D9Ex object and returns an interface to it.
    *
    * https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-direct3dcreate9ex
    *
    *@param sdk_version The value of this parameter should be @c D3D_SDK_VERSION.
    *@param unused Address of a pointer to an @c IDirect3D9Ex interface, representing the created @c IDirect3D9Ex object.
    */
    HRESULT WINAPI bbcf_im_direct_3d_create9_ex(UINT sdk_version, IDirect3D9Ex** unused)
    {
        using namespace bbcf_im;
        logger::instance()->write("Detoured call '%s'.", "Direct3DCreate9Ex");

        if (orig_direct_3d_create9_ex == nullptr)
        {
            return D3DERR_NOTAVAILABLE;
        }

        const auto result = orig_direct_3d_create9_ex(sdk_version, unused);
        if (d3d9_ex_wrapper == nullptr)
        {
            d3d9_ex_wrapper = std::make_unique<Direct3D9ExWrapper>(unused);
        }

        return result;
    }

    /**
    *@brief Create an effect from an ASCII or binary effect description.
    *
    * https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxcreateeffect
    *
    *@param device Pointer to the device that will create the effect.
    *@param src_data Pointer to a buffer containing an effect description.
    *@param src_data_len Length of the effect data, in bytes.
    *@param defines An optional NULL-terminated array of @c D3DXMACRO structures that describe preprocessor definitions. This value can be @c NULL.
    *@param include Optional interface pointer, @c ID3DXInclude, to use for handling @c #include directives.
    *@param flags If @c pSrcData contains a text effect, flags can be a combination of @c D3DXSHADER Flags and @c D3DXFX flags; otherwise, pSrcData contains a binary effect and the only flags honored are @c D3DXFX flags.
    *@param pool Pointer to a @c ID3DXEffectPool object to use for shared parameters.
    *@param effect Returns a pointer to an @c ID3DXEffect interface.
    *@param compilation_errors Returns a buffer containing a listing of compile errors.
    */
    HRESULT WINAPI bbcf_im_d3d_create_effect(LPDIRECT3DDEVICE9 device, LPCVOID src_data, UINT src_data_len,
        CONST D3DXMACRO* defines, LPD3DXINCLUDE include, DWORD flags, LPD3DXEFFECTPOOL pool,
        LPD3DXEFFECT* effect, LPD3DXBUFFER* compilation_errors)
    {
        using namespace bbcf_im;
        logger::instance()->write("Detoured call '%s'.", "D3DXCreateEffect");

        const auto result = orig_d3d_create_effect(device, src_data, src_data_len, defines, include,
            flags, pool, effect, compilation_errors);

        if (SUCCEEDED(result) && d3d9x_effect_wrapper == nullptr)
        {
            d3d9x_effect_wrapper = std::make_unique<ID3DXEffectWrapper>(&effect);
        }

        return result;
    }

    /**
    *@brief Creates a sprite object which is associated with a particular device.
    *
    * https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxcreatesprite
    *
    *@param device Pointer to an @c IDirect3DDevice9 interface, the device to be associated with the sprite.
    *@param ptr_sprite Address of a pointer to an @c ID3DXSprite interface.
    */
    HRESULT WINAPI bbcf_im_d3d_create_sprite(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE* ptr_sprite)
    {
        using namespace bbcf_im;
        logger::instance()->write("Detoured call '%s'.", "D3DXCreateSprint");

        const auto result = orig_d3d_create_sprite(device, ptr_sprite);
        if (SUCCEEDED(result) && d3d9x_sprite_wrapper == nullptr)
        {
            d3d9x_sprite_wrapper = std::make_unique<ID3DXSpriteWrapper>(&ptr_sprite);
        }

        return result;
    }
}

bool bbcf_im::install_d3d_hooks()
{
    if (detours_installed) return true;
    std::lock_guard guard(detours_mutex);
    if (detours_installed) return true;

    module_d3d9 = LoadLibrary(_T("d3d9.dll"));
    if (module_d3d9 == nullptr || module_d3d9 == INVALID_HANDLE_VALUE)
    {
        const auto error_code = GetLastError();
        logger::instance()->write("Failed to load d3d9.dll. Error: %d", error_code);
        return false;
    }

    module_d3dx9_43 = LoadLibrary(_T("d3dx9_43.dll"));
    if (module_d3dx9_43 == nullptr || module_d3dx9_43 == INVALID_HANDLE_VALUE)
    {
        const auto error_code = GetLastError();
        logger::instance()->write("Failed to load d3dx9_43.dll. Error: %d", error_code);
        return false;
    }

    base_direct_3d_create9_ex = reinterpret_cast<PBYTE>(GetProcAddress(module_d3d9, "Direct3DCreate9Ex"));
    base_d3d_create_effect    = reinterpret_cast<PBYTE>(GetProcAddress(module_d3dx9_43, "D3DXCreateEffect"));
    base_d3d_create_sprite    = reinterpret_cast<PBYTE>(GetProcAddress(module_d3dx9_43, "D3DXCreateSprite"));

    LPVOID tmp_direct_3d_create9_ex = nullptr;
    LPVOID tmp_d3dx_create_effect = nullptr;
    LPVOID tmp_d3dx_create_sprite = nullptr;

    //-------------------------------------------

    auto hook_status = MH_CreateHook(base_direct_3d_create9_ex, reinterpret_cast<LPVOID>(bbcf_im_direct_3d_create9_ex),
        &tmp_direct_3d_create9_ex);

    if (hook_status != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to create hook for Direct3DCreate9Ex. Error: %s", error_desc.c_str());
        return false;
    }

    orig_direct_3d_create9_ex = (func_Direct3DCreate9Ex)tmp_direct_3d_create9_ex;
    if (MH_EnableHook(base_direct_3d_create9_ex) != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to enable hook for Direct3DCreate9Ex. Error: %s", error_desc.c_str());
        return false;
    }

    logger::instance()->write("Direct3DCreate9Ex hooked and enabled successfully!");

    //-------------------------------------------

    hook_status = MH_CreateHook(base_d3d_create_effect, reinterpret_cast<LPVOID>(bbcf_im_d3d_create_effect),
        &tmp_d3dx_create_effect);

    if (hook_status != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to create hook for D3DXCreateEffect. Error: %s", error_desc.c_str());
        return false;
    }

    orig_d3d_create_effect = (func_D3DCreateEffect)tmp_d3dx_create_effect;
    if (MH_EnableHook(base_d3d_create_effect) != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to enable hook for D3D9XEffect. Error: %s", error_desc.c_str());
        return false;
    }

    logger::instance()->write("D3D9XEffect hooked and enabled successfully!");

    //-------------------------------------------

    hook_status = MH_CreateHook(base_d3d_create_sprite, reinterpret_cast<LPVOID>(bbcf_im_d3d_create_sprite),
        &tmp_d3dx_create_sprite);

    if (hook_status != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to create hook for D3DXCreateSprite. Error: %s", error_desc.c_str());
        return false;
    }


    orig_d3d_create_sprite = (func_D3DCreateSprite)tmp_d3dx_create_sprite;
    if (MH_EnableHook(base_d3d_create_sprite) != MH_OK)
    {
        const auto error_desc = hook_tools::mh_status_string(hook_status);
        logger::instance()->write("Failed to enable hook for D3DXCreateSprite. Error: %s", error_desc.c_str());
        return false;
    }

    logger::instance()->write("D3DXCreateSprite hooked and enabled successfully!");

    //-------------------------------------------

    //orig_direct_3d_create9_ex = (func_Direct3DCreate9Ex)DetourFunction(ptr_direct_3d_create9_ex, reinterpret_cast<PBYTE>(bbcf_im_direct_3d_create9_ex));
    //orig_d3d_create_effect    = (func_D3DCreateEffect)DetourFunction(ptr_d3d_create_effect, reinterpret_cast<PBYTE>(bbcf_im_d3d_create_effect));

    return detours_installed = true;
}

bool bbcf_im::remove_d3d_hooks()
{
    MH_DisableHook(base_d3d_create_sprite);
    MH_DisableHook(base_d3d_create_effect);
    MH_DisableHook(base_direct_3d_create9_ex);

    if (orig_d3d_create_sprite != nullptr)
        MH_RemoveHook(base_d3d_create_sprite);

    if (orig_d3d_create_effect != nullptr)
        MH_RemoveHook(base_d3d_create_effect);

    if (orig_direct_3d_create9_ex != nullptr)
        MH_RemoveHook(base_direct_3d_create9_ex);

    return true;
}
