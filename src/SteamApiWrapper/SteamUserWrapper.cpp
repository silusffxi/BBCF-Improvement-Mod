#include "SteamUserWrapper.h"

#include "../logger.h"
#include "Core/utils.h"

SteamUserWrapper::SteamUserWrapper(ISteamUser** pSteamUser)
{
	LOG(7, "%s", "SteamUserWrapper")
	LOG(7, "    - before: *pSteamUser: 0x%p, thispointer: 0x%p\n", *pSteamUser, this);

	m_SteamUser = *pSteamUser;
	void* thisAddress = this;
	WriteToProtectedMemory((uintptr_t)pSteamUser, (char*)&thisAddress, 4); //basically *pSteamUser = this;

	LOG(7, "    - after: *pSteamUser: 0x%p, m_SteamUser: 0x%p\n", *pSteamUser, m_SteamUser);
}

SteamUserWrapper::~SteamUserWrapper()
{
}

HSteamUser SteamUserWrapper::GetHSteamUser()
{
	LOG(7, "%s", "GetHSteamUser")
	return m_SteamUser->GetHSteamUser();
}

bool SteamUserWrapper::BLoggedOn()
{
	LOG(7, "%s", "BLoggedOn")
	return m_SteamUser->BLoggedOn();
}

CSteamID SteamUserWrapper::GetSteamID()
{
	LOG(7, "%s", "GetSteamID")
	return m_SteamUser->GetSteamID();
}

int SteamUserWrapper::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	LOG(7, "%s", "InitiateGameConnection")
	return m_SteamUser->InitiateGameConnection(pAuthBlob, cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}

void SteamUserWrapper::TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
{
	LOG(7, "%s", "TerminateGameConnection")
	return m_SteamUser->TerminateGameConnection(unIPServer, usPortServer);
}

void SteamUserWrapper::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo)
{
	LOG(7, "%s", "TrackAppUsageEvent")
	return m_SteamUser->TrackAppUsageEvent(gameID, eAppUsageEvent, pchExtraInfo);
}

bool SteamUserWrapper::GetUserDataFolder(char *pchBuffer, int cubBuffer)
{
	LOG(7, "%s", "GetUserDataFolder")
	return m_SteamUser->GetUserDataFolder(pchBuffer, cubBuffer);
}

void SteamUserWrapper::StartVoiceRecording()
{
	LOG(7, "%s", "StartVoiceRecording")
	return m_SteamUser->StartVoiceRecording();
}

void SteamUserWrapper::StopVoiceRecording()
{
	LOG(7, "%s", "StopVoiceRecording")
	return m_SteamUser->StopVoiceRecording();
}

EVoiceResult SteamUserWrapper::GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated)
{
	LOG(7, "%s", "GetAvailableVoice")
	return m_SteamUser->GetAvailableVoice(pcbCompressed, pcbUncompressed_Deprecated, nUncompressedVoiceDesiredSampleRate_Deprecated);
}

EVoiceResult SteamUserWrapper::GetVoice(bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed_Deprecated, 
	void *pUncompressedDestBuffer_Deprecated, uint32 cbUncompressedDestBufferSize_Deprecated, uint32 *nUncompressBytesWritten_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated)
{
	LOG(7, "%s", "GetVoice")
	return m_SteamUser->GetVoice(bWantCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, bWantUncompressed_Deprecated, pUncompressedDestBuffer_Deprecated, 
		cbUncompressedDestBufferSize_Deprecated, nUncompressBytesWritten_Deprecated, nUncompressedVoiceDesiredSampleRate_Deprecated);
}

EVoiceResult SteamUserWrapper::DecompressVoice(const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
{
	LOG(7, "%s", "DecompressVoice")
	return m_SteamUser->DecompressVoice(pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, nDesiredSampleRate);
}

uint32 SteamUserWrapper::GetVoiceOptimalSampleRate()
{
	LOG(7, "%s", "GetVoiceOptimalSampleRate")
	return m_SteamUser->GetVoiceOptimalSampleRate();
}

HAuthTicket SteamUserWrapper::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	LOG(7, "%s", "GetAuthSessionTicket")
	return m_SteamUser->GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket);
}

EBeginAuthSessionResult SteamUserWrapper::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	LOG(7, "%s", "BeginAuthSession")
	return m_SteamUser->BeginAuthSession(pAuthTicket, cbAuthTicket, steamID);
}

void SteamUserWrapper::EndAuthSession(CSteamID steamID)
{
	LOG(7, "%s", "EndAuthSession")
	return m_SteamUser->EndAuthSession(steamID);
}

void SteamUserWrapper::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	LOG(7, "%s", "CancelAuthTicket")
	return m_SteamUser->CancelAuthTicket(hAuthTicket);
}

EUserHasLicenseForAppResult SteamUserWrapper::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	LOG(7, "%s", "UserHasLicenseForApp")
	return m_SteamUser->UserHasLicenseForApp(steamID, appID);
}

bool SteamUserWrapper::BIsBehindNAT()
{
	LOG(7, "%s", "BIsBehindNAT")
    return m_SteamUser->BIsBehindNAT();
}

void SteamUserWrapper::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
	LOG(7, "%s", "AdvertiseGame")
	return m_SteamUser->AdvertiseGame(steamIDGameServer, unIPServer, usPortServer);
}

CALL_RESULT(EncryptedAppTicketResponse_t)
SteamAPICall_t SteamUserWrapper::RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude)
{
	LOG(7, "%s", "RequestEncryptedAppTicket")
	return m_SteamUser->RequestEncryptedAppTicket(pDataToInclude, cbDataToInclude);
}

bool SteamUserWrapper::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	LOG(7, "%s", "GetEncryptedAppTicket")
	return m_SteamUser->GetEncryptedAppTicket(pTicket, cbMaxTicket, pcbTicket);
}

int SteamUserWrapper::GetGameBadgeLevel(int nSeries, bool bFoil)
{
	LOG(7, "%s", "GetGameBadgeLevel")
	return m_SteamUser->GetGameBadgeLevel(nSeries, bFoil);
}

int SteamUserWrapper::GetPlayerSteamLevel()
{
	LOG(7, "%s", "GetPlayerSteamLevel")
	return m_SteamUser->GetPlayerSteamLevel();
}

CALL_RESULT(StoreAuthURLResponse_t)
SteamAPICall_t SteamUserWrapper::RequestStoreAuthURL(const char *pchRedirectURL)
{
	LOG(7, "%s", "RequestStoreAuthURL")
	return m_SteamUser->RequestStoreAuthURL(pchRedirectURL);
}

bool SteamUserWrapper::BIsPhoneVerified()
{
	LOG(7, "%s", "BIsPhoneVerified")
	return m_SteamUser->BIsPhoneVerified();
}

bool SteamUserWrapper::BIsTwoFactorEnabled()
{
	LOG(7, "%s", "BIsTwoFactorEnabled")
	return m_SteamUser->BIsTwoFactorEnabled();
}

bool SteamUserWrapper::BIsPhoneIdentifying()
{
	LOG(7, "%s", "BIsPhoneIdentifying")
	return m_SteamUser->BIsPhoneIdentifying();
}

bool SteamUserWrapper::BIsPhoneRequiringVerification()
{
	LOG(7, "%s", "BIsPhoneRequiringVerification")
	return m_SteamUser->BIsPhoneRequiringVerification();
}
