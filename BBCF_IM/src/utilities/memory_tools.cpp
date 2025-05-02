#include <cstdint>
#include "../globals.hpp"
#include "../logger.h"
#include "memory_tools.h"

using namespace bbcf_im;

char* memory_tools::get_bbcf_base_address()
{
    // We can just grab the path to BBCF.exe from the globals
    // that were populated when the DLL was attached to the process.
    const auto bbcf_path = globals::host_process_path;

    auto bbcf_module = GetModuleHandleW(bbcf_path.c_str());
    if (bbcf_module == nullptr || bbcf_module == INVALID_HANDLE_VALUE)
    {
        const auto err = GetLastError();
        LOG(1, "Failed to get handle to BBCF.exe. Error: 0x%08x", err)
        return nullptr;
    }

    MODULEINFO mod_info = { };
    if (!GetModuleInformation(GetCurrentProcess(), bbcf_module, &mod_info, sizeof MODULEINFO))
    {
        const auto err = GetLastError();
        LOG(1, "Failed to get MODULEINFO for BBCF.exe. Error: 0x%08x", err)
        CloseHandle(bbcf_module);
        return nullptr;
    }

    const auto base_ptr = static_cast<char*>(mod_info.lpBaseOfDll);
    CloseHandle(bbcf_module);
    return base_ptr;
}
