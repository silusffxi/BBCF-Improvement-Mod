#include "SteamUtilsWrapper.h"

#include "../logger.h"
#include "Core/utils.h"

SteamUtilsWrapper::SteamUtilsWrapper(ISteamUtils** pSteamUtils)
{
	LOG(7, "%s", "SteamUtilsWrapper")
	LOG(7, "    - before: *pSteamUtils: 0x%p, thispointer: 0x%p", *pSteamUtils, this)

	m_SteamUtils = *pSteamUtils;
	void* thisAddress = this;
	WriteToProtectedMemory((uintptr_t)pSteamUtils, (char*)&thisAddress, 4); //basically *pSteamUtils = this;

	LOG(7, "    - after: *pSteamUtils: 0x%p, m_SteamUtils: 0x%p", *pSteamUtils, m_SteamUtils)
}

SteamUtilsWrapper::~SteamUtilsWrapper()
{
}

uint32 SteamUtilsWrapper::GetSecondsSinceAppActive()
{
	LOG(7, "%s", "GetSecondsSinceAppActive")
	return m_SteamUtils->GetSecondsSinceAppActive();
}

uint32 SteamUtilsWrapper::GetSecondsSinceComputerActive()
{
	LOG(7, "%s", "GetSecondsSinceComputerActive")
	return m_SteamUtils->GetSecondsSinceComputerActive();
}

EUniverse SteamUtilsWrapper::GetConnectedUniverse()
{
	LOG(7, "%s", "GetConnectedUniverse")
	return m_SteamUtils->GetConnectedUniverse();
}

uint32 SteamUtilsWrapper::GetServerRealTime()
{
	LOG(7, "%s", "GetServerRealTime")
	return m_SteamUtils->GetServerRealTime();
}

const char *SteamUtilsWrapper::GetIPCountry()
{
	LOG(7, "%s", "GetIPCountry")
	return m_SteamUtils->GetIPCountry();
}

bool SteamUtilsWrapper::GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight)
{
	LOG(7, "%s", "GetImageSize")
	return m_SteamUtils->GetImageSize(iImage, pnWidth, pnHeight);
}

bool SteamUtilsWrapper::GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize)
{
	LOG(7, "%s", "GetImageRGBA")
	return m_SteamUtils->GetImageRGBA(iImage, pubDest, nDestBufferSize);
}

bool SteamUtilsWrapper::GetCSERIPPort(uint32 *unIP, uint16 *usPort)
{
	LOG(7, "%s", "GetCSERIPPort")
	return m_SteamUtils->GetCSERIPPort(unIP, usPort);
}

uint8 SteamUtilsWrapper::GetCurrentBatteryPower()
{
	LOG(7, "%s", "GetCurrentBatteryPower")
	return m_SteamUtils->GetCurrentBatteryPower();
}

uint32 SteamUtilsWrapper::GetAppID()
{
	LOG(7, "%s", "GetAppID")
	return m_SteamUtils->GetAppID();
}

void SteamUtilsWrapper::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
{
	LOG(7, "%s", "SetOverlayNotificationPosition")
	return m_SteamUtils->SetOverlayNotificationPosition(eNotificationPosition);
}

bool SteamUtilsWrapper::IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed)
{
	LOG(7, "%s", "IsAPICallCompleted")
	return m_SteamUtils->IsAPICallCompleted(hSteamAPICall, pbFailed);
}

ESteamAPICallFailure SteamUtilsWrapper::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
{
	LOG(7, "%s", "GetAPICallFailureReason")
	return m_SteamUtils->GetAPICallFailureReason(hSteamAPICall);
}

bool SteamUtilsWrapper::GetAPICallResult(SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
{
	LOG(7, "%s", "GetAPICallResult")
	return m_SteamUtils->GetAPICallResult(hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}

// Deprecated. Applications should use SteamAPI_RunCallbacks() instead. Game servers do not need to call this function.
void SteamUtilsWrapper::RunFrame()
{
	LOG(1, "%s", "RunFrame DEPRECATED!")
	return;
}

uint32 SteamUtilsWrapper::GetIPCCallCount()
{
	LOG(7, "%s", "GetIPCCallCount")
	return m_SteamUtils->GetIPCCallCount();
}

void SteamUtilsWrapper::SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
{
	LOG(7, "%s", "SetWarningMessageHook")
	return m_SteamUtils->SetWarningMessageHook(pFunction);
}

bool SteamUtilsWrapper::IsOverlayEnabled()
{
	LOG(7, "%s", "IsOverlayEnabled")
	return m_SteamUtils->IsOverlayEnabled();
}

bool SteamUtilsWrapper::BOverlayNeedsPresent()
{
	LOG(7, "%s", "BOverlayNeedsPresent")
	return m_SteamUtils->BOverlayNeedsPresent();
}

CALL_RESULT(CheckFileSignature_t)
SteamAPICall_t SteamUtilsWrapper::CheckFileSignature(const char *szFileName)
{
	LOG(7, "%s", "CheckFileSignature")
	return m_SteamUtils->CheckFileSignature(szFileName);
}

bool SteamUtilsWrapper::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax, const char *pchExistingText)
{
	LOG(7, "%s", "ShowGamepadTextInput")
	return m_SteamUtils->ShowGamepadTextInput(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText);
}

uint32 SteamUtilsWrapper::GetEnteredGamepadTextLength()
{
	LOG(7, "%s", "GetEnteredGamepadTextLength")
	return m_SteamUtils->GetEnteredGamepadTextLength();
}

bool SteamUtilsWrapper::GetEnteredGamepadTextInput(char *pchText, uint32 cchText)
{
	LOG(7, "%s", "GetEnteredGamepadTextInput")
	return m_SteamUtils->GetEnteredGamepadTextInput(pchText, cchText);
}

const char *SteamUtilsWrapper::GetSteamUILanguage()
{
	LOG(7, "%s", "GetSteamUILanguage")
	return m_SteamUtils->GetSteamUILanguage();
}

bool SteamUtilsWrapper::IsSteamRunningInVR()
{
	LOG(7, "%s", "IsSteamRunningInVR")
	return m_SteamUtils->IsSteamRunningInVR();
}

void SteamUtilsWrapper::SetOverlayNotificationInset(int nHorizontalInset, int nVerticalInset)
{
	LOG(7, "%s", "SetOverlayNotificationInset")
	return m_SteamUtils->SetOverlayNotificationInset(nHorizontalInset, nVerticalInset);
}

bool SteamUtilsWrapper::IsSteamInBigPictureMode()
{
	LOG(7, "%s", "IsSteamInBigPictureMode")
	return m_SteamUtils->IsSteamInBigPictureMode();
}

void SteamUtilsWrapper::StartVRDashboard()
{
	LOG(7, "%s", "StartVRDashboard")
	return m_SteamUtils->StartVRDashboard();
}

bool SteamUtilsWrapper::IsVRHeadsetStreamingEnabled()
{
	LOG(7, "%s", "IsVRHeadsetStreamingEnabled")
	return m_SteamUtils->IsVRHeadsetStreamingEnabled();
}

void SteamUtilsWrapper::SetVRHeadsetStreamingEnabled(bool bEnabled)
{
	LOG(7, "%s", "SetVRHeadsetStreamingEnabled")
	return m_SteamUtils->SetVRHeadsetStreamingEnabled(bEnabled);
}
