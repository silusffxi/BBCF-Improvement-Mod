#include <cstdarg>
#include <ctime>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <sstream>
#include <utility>
#include "platform/filesystem.hpp"
#include "Core/Settings.h"
#include "utilities/string_tools.h"
#include "logger.h"

inline void bbcf_im_log_msg(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    bbcf_im::logger::instance()->write(message, args);
    va_end(args);
}

inline void bbcf_im_log_msg(const uint8_t level, const char* message, ...)
{
    if (level < DEBUG_LOG_LEVEL) return;

    va_list args;
    va_start(args, message);
    bbcf_im::logger::instance()->write(message, args);
    va_end(args);
}

bool bbcf_im_log_hook_succeeded(const PBYTE address, const char* func_name)
{
    if (!address)
    {
        LOG(2, "Failed to hook '%s'!", func_name)
        return false;
    }

    LOG(2, "Hook set: 0x%p - %s", address, func_name)
    return true;
}

void bbcf_im_log_settings()
{
    LOG(1, "%s", "settings.ini config:\n")

    std::stringstream output;
#define SETTING(type, var, ini_str, default_val) \
    output << "    - " << (ini_str) << " = " << Settings::settingsIni.##var << "\n";
#include "Core/settings.def"
#undef SETTING

    LOG(1, "%s", output.str().c_str())
}

using namespace bbcf_im;

std::unique_ptr<logger> logger::_instance = nullptr;

std::once_flag logger::_setup_once;

logger::logger(std::filesystem::path log_file_path, FILE* file) :
    _log_file(file),
    _log_file_path(std::move(log_file_path))
{
}

logger::~logger()
{
    if (_log_file != nullptr)
    {
        fclose(_log_file);
        _log_file = nullptr;
    }
}

void logger::write(const char* message, ...) const
{
    if (message == nullptr) return;

    va_list args;
    va_start(args, message);
    write(message, args);
    va_end(args);
}

void logger::write(const char* message, const va_list args) const
{
    if (message == nullptr) return;

    auto _ = vfprintf_s(_log_file, message, args);
    _ = fprintf_s(_log_file, "%c", '\n');
    _ = fflush(_log_file);
}

bool logger::create(const std::filesystem::path& log_dir)
{
    auto setup_ok = false;
    std::call_once(_setup_once, [&]
    {
        setup_ok = create_internal(log_dir);
    });

    return setup_ok;
}

void logger::shutdown()
{
    if (_instance != nullptr)
    {
        _instance.reset();
        _instance = nullptr;
    }
}

logger* logger::instance()
{
    return _instance.get();
}

bool logger::create_internal(const std::filesystem::path& log_dir)
{
    if (_instance != nullptr)
    {
        return true;
    }

    // Ensure our log directory exists before we try to write to it.
    if (!platform::filesystem::exists(log_dir) && !platform::filesystem::create_directory(log_dir))
    {
        return false;
    }

    const auto log_file_path = log_dir / L"debug.log";

    FILE* file_ptr = nullptr;
    auto err_result = fopen_s(&file_ptr, log_file_path.string().c_str(), "w");
    if (err_result != 0)
        return false;

    _instance = std::make_unique<logger>(log_file_path, file_ptr);
    const auto start_timestamp_str = timestamp_string();

    _instance->write("BBCF_FIX START - %s", start_timestamp_str.c_str());
    _instance->write("==================================================");
    return true;
}
