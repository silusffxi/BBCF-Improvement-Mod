#pragma once
#include <stdint.h>
#include "platform.h"

#define DEBUG_LOG_LEVEL	5 //0 = highest, 7 = lowest priority
#define FORCE_LOGGING 0

#if defined(_DEBUG) || FORCE_LOGGING == 1
#define ENABLE_LOGGING 1
#endif

inline void bbcf_im_log_msg(const char* message, ...);
inline void bbcf_im_log_msg(uint8_t level, const char* message, ...);

bool bbcf_im_log_hook_succeeded(PBYTE address, const char* func_name);
void bbcf_im_log_settings();

#ifdef ENABLE_LOGGING
#define LOG(_level, _str, ...) { \
    if (DEBUG_LOG_LEVEL >= _level) { bbcf_im_log_msg(_str, __VA_ARGS__); }}

//Use this to log in naked asm functions
#define LOG_ASM(_level, _str, ...) { \
    __asm{__asm pushad }; \
    if (DEBUG_LOG_LEVEL >= _level) { {bbcf_im_log_msg(_str, __VA_ARGS__);} } \
    __asm{__asm popad }; }
#else
#define LOG(_level, _str, ...) {}

//Use this to log in naked asm functions
#define LOG_ASM(_level, _str, ...) {}
#endif

#if defined(__cplusplus)
#include <cstdarg>
#include <filesystem>
#include <memory>
#include <mutex>

namespace bbcf_im
{
    class logger
    {
        static std::unique_ptr<logger> _instance;

        static std::once_flag _setup_once;

        FILE* _log_file = nullptr;

        std::filesystem::path _log_file_path;

    public:
        logger(std::filesystem::path log_file_path, FILE* file);
        ~logger();

        logger(const logger&) = default;
        logger(logger&&) = default;

        logger& operator=(const logger&) = default;
        logger& operator=(logger&&) = default;

        void write(const char* message, ...) const;
        void write(const char* message, va_list args) const;

        static bool create(const std::filesystem::path& log_dir);
        static void shutdown();

        static logger* instance();

    private:
        static bool create_internal(const std::filesystem::path& log_dir);
    };
}
#endif