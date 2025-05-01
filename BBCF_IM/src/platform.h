#pragma once
// min and max from the Windows API need to be included since
// there are a number of things that rely on it still.
//#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <combaseapi.h> // Required in order to get "interface" to work correctly.
#include <shellapi.h>
#include <atlstr.h>
#include <wininet.h>
#include <DbgHelp.h>
