#pragma once
#include <filesystem>
#include <string>

/**
*@brief Indicates that the Windows API should be used for file system interactions
*       rather than std::filesystem. Set this to 0 in order to use std::filesystem.
*/
#define BBCF_IM_FILESYSTEM_USE_WINDOWS_API 1

namespace bbcf_im::platform
{
    class filesystem
    {
    public:
        static bool create_directory(const std::string& path);
        static bool create_directory(const std::wstring& path);
        static std::filesystem::path get_system_directory();
    };
}
