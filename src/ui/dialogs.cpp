#include <string>
#include "../platform.h"
#include "dialogs.hpp"

using namespace bbcf_im;
using namespace ui;

void dialogs::show_error(const std::string& title, const std::string& text, const HWND parent_window)
{
    show_error(title.c_str(), text.c_str(), parent_window);
}

void dialogs::show_error(const std::wstring& title, const std::wstring& text, const HWND parent_window)
{
    show_error(title.c_str(), text.c_str(), parent_window);
}

void dialogs::show_error(const char* title, const char* text, const HWND parent_window)
{
    MessageBoxA(parent_window, text, title, MB_OK | MB_ICONERROR);
}

void dialogs::show_error(const wchar_t* title, const wchar_t* text, const HWND parent_window)
{
    MessageBoxW(parent_window, text, title, MB_OK | MB_ICONERROR);
}
