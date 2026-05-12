#include <atomic>
#include <filesystem>
#include <mutex>
#include <thread>
#include "Core/interfaces.h"
#include "Core/Settings.h"
#include "Hooks/hooks_detours.h"
#include "Overlay/WindowManager.h"

#include "d3d/d3d_hooks.h"
#include "Hooks/hooks_bbcf.h"
#include "Hooks/hooks_detours.h"
#include "platform/filesystem.hpp"
#include "proxies/dinput8_proxy.h"
#include "ui/dialogs.hpp"
#include "utilities/crash_handler.h"
#include "utilities/hook_tools.hpp"
#include "utilities/memory_tools.h"
#include "platform.h"
#include "globals.hpp"
#include "logger.h"
#include <MinHook.h>
#include "bbcf_im.hpp"

using namespace bbcf_im;
namespace fs = std::filesystem;
namespace
{
    std::atomic_bool    bbcf_im_started = false;
    std::mutex          bbcf_im_start_mutex;

    /**
    *@brief Creates directories required by the DLL.
    */
    bool create_directories()
    {
        const auto bbcf_im_dir = globals::module_dir / L"BBCF_IM";
        if (!platform::filesystem::create_directory(bbcf_im_dir))
        {
            return false;
        }

        globals::bbcf_im_dir = bbcf_im_dir;
        return true;
    }

    /**
    *@brief Returns the path to the specified module.
    */
    fs::path get_module_file_path(const HMODULE mod)
    {
        TCHAR path_raw[MAX_PATH];
        const auto result = GetModuleFileName(mod, path_raw, MAX_PATH);
        if (result == 0)
        {
            ui::dialogs::show_error("BBCFIM", "Failed to get path to module.");
            return L"";
        }

        return { path_raw };
    }

    /**
    *@brief Returns the path to the executable that is hosting the DLL.
    */
    fs::path get_host_process_path()
    {
        const auto host_mod = GetModuleHandle(nullptr);
        if (host_mod == nullptr || host_mod == INVALID_HANDLE_VALUE)
        {
            ui::dialogs::show_error("BBCFIM", "Failed to get module for process that is hosting BBCF_IM.");
            return L"";
        }

        return get_module_file_path(host_mod);
    }

    /**
    *@brief Sets up the dinput8 proxy.
    */
    bool setup_dinput8_proxy()
    {
        bool dinput_ok;
        const auto dinput_target = Settings::settingsIni.dinputDllWrapper;
        if (dinput_target == "none" || dinput_target.empty())
        {
            dinput_ok = proxies::dinput8_proxy::setup();
        }
        else
        {
            // Since we have something that looks like it may be a dinput8 proxy,
            // we'll attempt to construct a full path for the proxy DLL to load.
            const auto target_path = globals::module_dir / dinput_target;
            dinput_ok = proxies::dinput8_proxy::setup(target_path);
        }

        return dinput_ok;
    }
}

bool bbcf_im::start()
{
    if (bbcf_im_started) return bbcf_im_started;
    std::lock_guard guard(bbcf_im_start_mutex);
    if (bbcf_im_started) return bbcf_im_started;

    globals::host_process_id = GetCurrentProcessId();

    globals::host_process_path = get_host_process_path();
    globals::host_process_dir  = globals::host_process_path.parent_path();

    globals::module_path = get_module_file_path(globals::instance_module);
    globals::module_dir  = globals::module_path.parent_path();

    globals::bbcf_base_address = memory_tools::get_bbcf_base_address();

    create_directories();

    logger::create(globals::bbcf_im_dir);

    LOG(1, "%s", "Starting bbcf_im::start thread")

    SetUnhandledExceptionFilter(unhandled_exception_filter);

    if (!Settings::loadSettingsFile())
    {
        ExitProcess(0);
    }

    bbcf_im_log_settings();
    Settings::initSavedSettings();

    if (!setup_dinput8_proxy())
    {
        ui::dialogs::show_error("BBCFIM", "Could not load original dinput8.dll!");
        ExitProcess(0);
    }

    const auto mh_init_result = MH_Initialize();
    if (mh_init_result != MH_OK)
    {
        logger::instance()->write("Failed to initialize MinHook. Error: %s",
            hook_tools::mh_status_string(mh_init_result).c_str());

        ui::dialogs::show_error("BBCFIM", "Failed to initialize hooks.");
        return false;
    }

    if (!install_d3d_hooks())
    {
        ui::dialogs::show_error("BBCFIM", "Failed to install D3D hooks.");
        ExitProcess(ERROR_DLL_INIT_FAILED);
    }

    if (!placeHooks_detours())
    {
        ui::dialogs::show_error("BBCFIM", "Failed IAT hook");
        ExitProcess(0);
    }

    g_interfaces.pPaletteManager = new PaletteManager();

    return bbcf_im_started = true;
}

void bbcf_im::shutdown()
{
    if (!bbcf_im_started) return;

    LOG(1, "%s", "bbcf_im::shutdown")

    WindowManager::GetInstance().Shutdown();
    CleanupInterfaces();

    remove_d3d_hooks();
    const auto mh_shutdown_result = MH_Uninitialize();
    if (mh_shutdown_result != MH_OK)
    {
        logger::instance()->write("Failed to shutdown MinHook. Error: %s",
            hook_tools::mh_status_string(mh_shutdown_result).c_str());
    }

    proxies::dinput8_proxy::shutdown();
    logger::shutdown();
    bbcf_im_started = false;
}
