#include "hooks_detours.h"

#include "HookManager.h"

#include "Core/interfaces.h"
#include "../logger.h"
#include "D3D9EXWrapper/ID3D9Wrapper_Sprite.h"
#include "D3D9EXWrapper/ID3DXWrapper_Effect.h"
#include "D3D9EXWrapper/ID3D9EXWrapper.h"

#include <detours.h>

typedef SteamAPICall_t(__fastcall* RequestLobbyList_t)(ISteamMatchmaking*);
typedef bool (WINAPI* SteamAPI_Init_t)();
typedef HWND(__stdcall* CreateWindowExW_t)(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName,
	DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);

RequestLobbyList_t orig_RequestLobbyList;
SteamAPI_Init_t orig_SteamAPI_Init;
CreateWindowExW_t orig_CreateWindowExW;

DWORD SteamMatchmakingFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamMatchmaking()
{
	LOG_ASM(2, "%s", "GetSteamMatchmaking")

	__asm
	{
		call dword ptr[eax + 28h]
		/////
		pushad
		add esi, 10h
		mov g_tempVals.ppSteamMatchmaking, esi
		popad
		/////
		mov[esi + 10h], eax
		jmp[SteamMatchmakingFuncJmpBackAddr]
	}
}

DWORD SteamNetworkingFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamNetworking()
{
	LOG_ASM(2, "%s", "GetSteamNetworking")

	__asm
	{
		call dword ptr[eax + 40h]
		/////
		pushad
		add esi, 20h
		mov g_tempVals.ppSteamNetworking, esi
		popad
		/////
		mov[esi + 20h], eax
		jmp[SteamNetworkingFuncJmpBackAddr]
	}
}

DWORD SteamUserFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamUser()
{
	LOG_ASM(2, "%s", "GetSteamUser")

	__asm
	{
		call dword ptr[eax + 14h]
		/////
		pushad
		add esi, 4h
		mov g_tempVals.ppSteamUser, esi
		popad
		/////
		mov[esi + 4h], eax
		jmp[SteamUserFuncJmpBackAddr]
	}
}

DWORD SteamFriendsFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamFriends()
{
	LOG_ASM(2, "%s", "GetSteamFriends")

	__asm
	{
		call dword ptr[eax + 20h]
		/////
		pushad
		add esi, 8h
		mov g_tempVals.ppSteamFriends, esi
		popad
		/////
		mov[esi + 8h], eax
		jmp[SteamFriendsFuncJmpBackAddr]
	}
}

DWORD SteamUtilsFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamUtils()
{
	LOG_ASM(2, "%s", "GetSteamUtils")

	__asm
	{
		call dword ptr[eax + 24h]
		/////
		pushad
		add esi, 0Ch
		mov g_tempVals.ppSteamUtils, esi
		popad
		/////
		mov[esi + 0Ch], eax
		jmp[SteamUtilsFuncJmpBackAddr]
	}
}

DWORD SteamUserStatsFuncJmpBackAddr = 0;
void __declspec(naked)GetSteamUserStats()
{
	LOG_ASM(2, "%s", "GetSteamUserStats")

	__asm
	{
		call dword ptr[eax + 34h]
		/////
		pushad
		add esi, 14h
		mov g_tempVals.ppSteamUserStats, esi
		popad
		/////
		mov[esi + 14h], eax
		jmp[SteamUserStatsFuncJmpBackAddr]
	}
}

bool WINAPI hook_SteamAPI_Init()
{
	LOG(1, "%s", "SteamAPI_Init")

	bool ret = orig_SteamAPI_Init();

	SteamMatchmakingFuncJmpBackAddr = HookManager::SetHook("SteamMatchmaking", "\xff\x50\x28\x89\x46\x10\x85\xc0", "xxxxxxxx", 6, GetSteamMatchmaking);
	
	SteamNetworkingFuncJmpBackAddr = HookManager::SetHook("SteamNetworking", "\xff\x50\x40\x89\x46\x20\x85\xc0", "xxxxxxxx", 6, GetSteamNetworking);
	
	SteamUserFuncJmpBackAddr = HookManager::SetHook("SteamUser", "\xff\x50\x14\x89\x46\x04", "xxxxxx", 6, GetSteamUser);
	
	SteamFriendsFuncJmpBackAddr = HookManager::SetHook("SteamFriends", "\xff\x50\x20\x89\x46\x08", "xxxxxx", 6, GetSteamFriends);
	
	SteamUtilsFuncJmpBackAddr = HookManager::SetHook("SteamUtils", "\xff\x50\x24\x89\x46\x0c", "xxxxxx", 6, GetSteamUtils);
	
	SteamUserStatsFuncJmpBackAddr = HookManager::SetHook("SteamUserStats", "\xff\x50\x34\x89\x46\x14", "xxxxxx", 6, GetSteamUserStats);

	return ret;
}

HWND WINAPI hook_CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName,
	DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	LOG(7, "%s", "CreateWindowExW")
	static int counter = 1;
	HWND hWnd = orig_CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	if (SUCCEEDED(hWnd))
	{
		LOG(7, "\tSuccess: 0x%p\n", hWnd);
		if (counter == 2) // 2nd created window should be the correct one according to process hacker
		{
			LOG(2, "Correct window: 0x%p\n", hWnd);
			g_gameProc.hWndGameWindow = hWnd;
		}
	}
	counter++;
	return hWnd;
}

bool placeHooks_detours()
{
	LOG(1, "%s", "placeHooks_detours")

	HMODULE hM_steam_api = GetModuleHandleA("steam_api.dll");
	HMODULE hM_user32 = GetModuleHandleA("user32.dll");

    PBYTE pSteamAPI_Init = (PBYTE)GetProcAddress(hM_steam_api, "SteamAPI_Init");
	PBYTE pCreateWindowExW = (PBYTE)GetProcAddress(hM_user32, "CreateWindowExW");

	if (!bbcf_im_log_hook_succeeded((PBYTE)pSteamAPI_Init, "SteamAPI_Init"))
		return false;
	if (!bbcf_im_log_hook_succeeded((PBYTE)pCreateWindowExW, "CreateWindowExW"))
		return false;

	orig_SteamAPI_Init = (SteamAPI_Init_t)DetourFunction(pSteamAPI_Init, (LPBYTE)hook_SteamAPI_Init);
	orig_CreateWindowExW = (CreateWindowExW_t)DetourFunction(pCreateWindowExW, (LPBYTE)hook_CreateWindowExW);

	return true;
}