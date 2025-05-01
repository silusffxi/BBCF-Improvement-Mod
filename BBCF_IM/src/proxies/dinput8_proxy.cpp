#include <atomic>
#include <filesystem>
#include <mutex>
#include "../Core/logger.h"
#include "../platform.h"
#include "../platform/filesystem.hpp"
#include "dinput8_proxy.h"

namespace fs = std::filesystem;
using namespace bbcf_im;
using namespace proxies;
namespace
{
    HMODULE                 orig_dinput8             = nullptr;
    func_DirectInput8Create orig_direct_input_create = nullptr;
}

std::atomic_bool dinput8_proxy::_dinput8_loaded = false;
std::mutex       dinput8_proxy::_setup_mutex;

HRESULT dinput8_proxy::create(HINSTANCE instance, DWORD version, const IID& unique_id,
    LPVOID* receiver, LPUNKNOWN pUnkOuter)
{
    LOG(1, "DirectInput8Create\n");
    const auto result = orig_direct_input_create(instance, version, unique_id, receiver, pUnkOuter);
    LOG(1, "DirectInput8Create result: %d\n", result);

    return result;
}

bool dinput8_proxy::setup(const std::filesystem::path& dinput8_path)
{
    if (_dinput8_loaded) return true;
    std::lock_guard guard(_setup_mutex);
    if (_dinput8_loaded) return true;

    auto target_path = dinput8_path;
    if (dinput8_path.empty() || !fs::exists(target_path))
    {
        target_path = get_module_path();
    }

    orig_dinput8 = LoadLibraryW(target_path.c_str());
    if (orig_dinput8 == nullptr || orig_dinput8 == INVALID_HANDLE_VALUE)
        return false;

    orig_direct_input_create = (func_DirectInput8Create)GetProcAddress(orig_dinput8, "DirectInput8Create");
    if (orig_direct_input_create == nullptr)
    {
        FreeLibrary(orig_dinput8);
        return false;
    }

    return _dinput8_loaded = true;
}

bool dinput8_proxy::shutdown()
{
    if (!_dinput8_loaded) return true;

    orig_direct_input_create = nullptr;
    if (orig_dinput8 != nullptr)
    {
        FreeLibrary(orig_dinput8);
        orig_dinput8 = nullptr;
    }

    return _dinput8_loaded = false;
}

std::filesystem::path dinput8_proxy::get_module_path()
{
    return platform::filesystem::get_system_directory() / L"dinput8.dll";
}

/*extern "C" BBCF_IM_API*/ HRESULT WINAPI DirectInput8Create(HINSTANCE hInstance, DWORD dwVersion, const IID& riidlt,
    LPVOID* ppvOut, LPUNKNOWN pUnkOuter)
{
    return dinput8_proxy::create(hInstance, dwVersion, riidlt, ppvOut, pUnkOuter);
}