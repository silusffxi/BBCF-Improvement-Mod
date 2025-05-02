#include <string>
#include <filesystem>
#include "filesystem.hpp"
#if BBCF_IM_FILESYSTEM_USE_WINDOWS_API
#include "../platform.h"
#endif

using namespace bbcf_im;
using namespace platform;

namespace
{
#if !BBCF_IM_FILESYSTEM_USE_WINDOWS_API
    bool fs_create_directory(const std::filesystem::path& path)
    {
        namespace fs = std::filesystem;

        if (fs::exists(path) && fs::is_directory(path))
            return true;

        return fs::create_directory(path);
    }
#endif
}

bool filesystem::create_directory(const std::string& path)
{
#if BBCF_IM_FILESYSTEM_USE_WINDOWS_API
    if (exists(path))
        return true;

    return CreateDirectoryA(path.c_str(), nullptr);
#else
    return fs_create_directory(path);
#endif
}

bool filesystem::create_directory(const std::wstring& path)
{
#if BBCF_IM_FILESYSTEM_USE_WINDOWS_API
    if (exists(path))
        return true;

    return CreateDirectoryW(path.c_str(), nullptr);
#else
    return fs_create_directory(path);
#endif
}

std::filesystem::path filesystem::get_system_directory()
{
    TCHAR sys_dir_path[MAX_PATH];
    if (GetSystemDirectory(sys_dir_path, MAX_PATH) == 0)
        return L"";

    return { sys_dir_path };
}

bool filesystem::exists(const std::string& path)
{
#if BBCF_IM_FILESYSTEM_USE_WINDOWS_API
    return PathFileExistsA(path.c_str());
#else
    return std::filesystem::exists(path);
#endif
}

bool filesystem::exists(const std::wstring& path)
{
#if BBCF_IM_FILESYSTEM_USE_WINDOWS_API
    return PathFileExistsW(path.c_str());
#else
    return std::filesystem::exists(path);
#endif    
}
