#include <cstdint>
#include <cstdio>
#include <string>
#include <sstream>
#include "../globals.hpp"
#include "../logger.h"
#include "memory_tools.h"

using namespace bbcf_im;

char* bbcf_im_get_bbcf_base_address()
{
    return memory_tools::get_bbcf_base_address();
}

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
    return base_ptr;
}

std::string memory_tools::raw_memory_to_string(const uint8_t* src, const size_t length)
{
    std::stringstream output;
    for (size_t idx = 0; idx < length; idx++)
    {
        char tmp[3] = { };
        const auto result = sprintf_s(tmp, 3, "%02X", src[idx]);
        if (result == -1)
            continue;

        output << tmp;

        if (idx + 1 < length)
            output << ' ';
    }

    return output.str();
}
