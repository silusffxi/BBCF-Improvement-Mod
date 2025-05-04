#include <cstdint>
#include <filesystem>
#include <format>
#include <string>
#include "../globals.hpp"
#include "../ui/dialogs.hpp"
#include "string_tools.h"
#include "crash_handler.h"

using namespace bbcf_im;

typedef BOOL(WINAPI* func_MiniDumpWriteDump)(
    HANDLE                            process,
    DWORD                             process_id,
    HANDLE                            file,
    MINIDUMP_TYPE                     exception_param,
    PMINIDUMP_EXCEPTION_INFORMATION   exception_info,
    PMINIDUMP_USER_STREAM_INFORMATION user_stream_param,
    PMINIDUMP_CALLBACK_INFORMATION    callback_param);

LONG WINAPI unhandled_exception_filter(const PEXCEPTION_POINTERS ex_info)
{
    const auto dump_result = crash_handler::write_crash_dump(ex_info);
    ExitProcess(ERROR_UNHANDLED_EXCEPTION);
    return dump_result;
}

LONG crash_handler::write_crash_dump(const PEXCEPTION_POINTERS ex_info)
{
    // Information regarding how this function should operate and what should be returned:
    // https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-unhandledexceptionfilter#return-value

    // Load the dbghelp library and find the function to write the minidump file.
    auto dbghelp_module = LoadLibrary(_T("dbghelp"));
    if (dbghelp_module == nullptr || dbghelp_module == INVALID_HANDLE_VALUE)
    {
        ui::dialogs::show_error("BBCFIM", "Failed create crash dump.");
        return EXCEPTION_CONTINUE_SEARCH;
    }

    const auto minidump_create_dump = (func_MiniDumpWriteDump)GetProcAddress(dbghelp_module, "MiniDumpWriteDump");
    if (minidump_create_dump == nullptr)
    {
        ui::dialogs::show_error("BBCFMIM", "Failed to create crash dump.\nCould not load dbghelp.dll to write minidump file.");
        return EXCEPTION_CONTINUE_SEARCH;
    }

    const auto file_name = std::format("crash_{}.dmp", timestamp_string("%Y%m%d%H%M%S"));
    const auto file_path = globals::bbcf_im_dir / file_name;

    auto dump_file = CreateFileW(file_path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (dump_file == nullptr || dump_file == INVALID_HANDLE_VALUE)
    {
        const auto error_code = GetLastError();

        ui::dialogs::show_error("BBCFIM", std::format(
            "Failed to open crash dump file for writing.\nWindows Error: {:#08x}",
            static_cast<uint32_t>(error_code)));

        FreeLibrary(dbghelp_module);
        dbghelp_module = nullptr;
        return EXCEPTION_CONTINUE_SEARCH;
    }

    MINIDUMP_EXCEPTION_INFORMATION minidump_ex_info;
    minidump_ex_info.ThreadId          = GetCurrentThreadId();
    minidump_ex_info.ExceptionPointers = ex_info;
    minidump_ex_info.ClientPointers    = FALSE;

    const auto dump_created = minidump_create_dump(GetCurrentProcess(), GetCurrentProcessId(),
        dump_file, MiniDumpNormal, &minidump_ex_info, nullptr, nullptr);

    if (!dump_created)
    {
        const auto error_code = GetLastError();

        ui::dialogs::show_error("BBCFIM", std::format(
            "Failed to write crash dump.\nWindows Error: {:#08x}",
            static_cast<uint32_t>(error_code)));

        CloseHandle(dump_file);
        dump_file = nullptr;
        FreeLibrary(dbghelp_module);
        dbghelp_module = nullptr;
        return EXCEPTION_CONTINUE_SEARCH;
    }

    ui::dialogs::show_error("BBCFIM", std::format(
        "Unhandled exception occurred. A crash dump file has been written to:\n{}",
        file_path.string()));

    CloseHandle(dump_file);
    dump_file = nullptr;
    FreeLibrary(dbghelp_module);
    dbghelp_module = nullptr;
    return EXCEPTION_CONTINUE_SEARCH;
}
