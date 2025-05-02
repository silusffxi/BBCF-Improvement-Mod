#include "globals.hpp"
#include "bbcf_im.hpp"
#include "platform.h"
#include "utilities/debug_tools.hpp"

namespace
{
    BOOL handle_process_attach(HMODULE mod)
    {
        DisableThreadLibraryCalls(mod);
        bbcf_im::globals::instance_module = mod;
        BBCF_IM_DEBUG_WAIT_FOR_DEBUGGER();
        return bbcf_im::start();
    }

    BOOL handle_process_detach()
    {
        bbcf_im::shutdown();
        return TRUE;
    }

    BOOL handle_thread_attach(HMODULE mod)
    {
        return TRUE;
    }

    BOOL handle_thread_detach()
    {
        return TRUE;
    }
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        return handle_process_attach(hModule);
    case DLL_PROCESS_DETACH:
        return handle_process_detach();
    case DLL_THREAD_ATTACH:
        return handle_thread_attach(hModule);
    case DLL_THREAD_DETACH:
        return handle_thread_detach();
    default:
        return TRUE;
    }
}