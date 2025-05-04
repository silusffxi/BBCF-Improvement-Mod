#pragma once
#include "../platform.h"
#include "d3d.h"

/**
*@brief Creates an @c IDirect3D9Ex object and returns an interface to it.
*@param sdk_version The value of this parameter should be @c D3D_SDK_VERSION.
*@param unused_param2 Address of a pointer to an @c IDirect3D9Ex interface, representing the created @c IDirect3D9Ex object.
*/
typedef HRESULT(WINAPI* func_Direct3DCreate9Ex)(UINT sdk_version, IDirect3D9Ex** unused_param2);

/**
*@brief Create an effect from an ASCII or binary effect description.
*/
typedef HRESULT(WINAPI* func_D3DCreateEffect)(LPDIRECT3DDEVICE9, LPCVOID, UINT, CONST D3DXMACRO*,
    LPD3DXINCLUDE, DWORD, LPD3DXEFFECTPOOL, LPD3DXEFFECT*, LPD3DXBUFFER*);

/**
*@brief Creates a sprite object which is associated with a particular device.
*/
typedef HRESULT(WINAPI* func_D3DCreateSprite)(LPDIRECT3DDEVICE9, LPD3DXSPRITE*);

namespace bbcf_im
{
    /**
    *@brief Installs the detours/hooks for functions related to DirectX.
    */
    bool install_d3d_hooks();

    /**
    *@brief Disables and removes hooks for functions related to DirectX.
    */
    bool remove_d3d_hooks();
}