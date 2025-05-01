#include <filesystem>
#include <thread>
#include "Core/crashdump.h"
#include "Core/interfaces.h"
#include "logger.h"
#include "Core/Settings.h"
#include "Hooks/hooks_detours.h"
#include "Overlay/WindowManager.h"

#include "platform/filesystem.hpp"
#include "proxies/dinput8_proxy.h"
#include "ui/dialogs.hpp"
#include "platform.h"
#include "globals.hpp"
#include "bbcf_im.hpp"

using namespace bbcf_im;
namespace fs = std::filesystem;
namespace
{
    /**
    *@brief Creates directories required by the DLL.
    */
    bool create_directories()
    {
        LOG(1, "create_directories\n");

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
    globals::host_process_id = GetCurrentProcessId();

    globals::host_process_path = get_host_process_path();
    globals::host_process_dir  = globals::host_process_path.parent_path();

    globals::module_path = get_module_file_path(globals::instance_module);
    globals::module_dir  = globals::module_path.parent_path();

    openLogger();

    LOG(1, "Starting BBCF_IM_Start thread\n");

    create_directories();
    SetUnhandledExceptionFilter(UnhandledExFilter);

    if (!Settings::loadSettingsFile())
    {
        ExitProcess(0);
    }
    logSettingsIni();
    Settings::initSavedSettings();

    if (!setup_dinput8_proxy())
    {
        ui::dialogs::show_error("BBCFIM", "Could not load original dinput8.dll!");
        ExitProcess(0);
    }

    if (!placeHooks_detours())
    {
        ui::dialogs::show_error("BBCFIM", "Failed IAT hook");
        ExitProcess(0);
    }

    g_interfaces.pPaletteManager = new PaletteManager();

    return true;
}

void bbcf_im::shutdown()
{
    LOG(1, "BBCF_IM_Shutdown\n");

    WindowManager::GetInstance().Shutdown();
    CleanupInterfaces();
    proxies::dinput8_proxy::shutdown();
    closeLogger();
}
