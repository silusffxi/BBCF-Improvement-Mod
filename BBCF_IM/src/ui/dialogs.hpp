#pragma once
#include <string>
#include "../platform.h"

namespace bbcf_im::ui
{
    class dialogs
    {
    public:
        static void show_error(const std::string& title, const std::string& text,
            HWND parent_window = nullptr);
        static void show_error(const std::wstring& title, const std::wstring& text,
            HWND parent_window = nullptr);
        static void show_error(const char* title, const char* text,
            HWND parent_window = nullptr);
        static void show_error(const wchar_t* title, const wchar_t* text,
            HWND parent_window = nullptr);
    };
}
