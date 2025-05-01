#pragma once
#include <cstdint>
#include <filesystem>
#include "platform.h"

namespace bbcf_im::globals
{
    extern std::filesystem::path bbcf_im_dir;

    extern std::filesystem::path host_process_dir;
    extern std::filesystem::path host_process_path;

    extern uint32_t host_process_id;

    extern std::filesystem::path module_dir;
    extern std::filesystem::path module_path;

    /**
    *@brief The @c HMODULE that was passed into @c DllMain
    */
    extern HMODULE instance_module;
}
