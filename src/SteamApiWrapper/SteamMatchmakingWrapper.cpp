#include "SteamMatchmakingWrapper.h"

#include "Core/interfaces.h"
#include "../logger.h"
#include "Core/utils.h"
#include "Game/gamestates.h"

SteamMatchmakingWrapper::SteamMatchmakingWrapper(ISteamMatchmaking** pSteamMatchmaking)
{
	LOG(2, "%s", "SteamMatchmakingWrapper")
	LOG(2, "    - before: *pSteamMatchmaking: 0x%p, thispointer: 0x%p", *pSteamMatchmaking, this)

	m_SteamMatchmaking = *pSteamMatchmaking;
	void* thisAddress = this;
	WriteToProtectedMemory((uintptr_t)pSteamMatchmaking, (char*)&thisAddress, 4); //basically *pSteamMatchmaking = this;

	LOG(2, "    - after: *pSteamMatchmaking: 0x%p, m_SteamMatchmaking: 0x%p", *pSteamMatchmaking, m_SteamMatchmaking)
}

SteamMatchmakingWrapper::~SteamMatchmakingWrapper()
{
}

int SteamMatchmakingWrapper::GetFavoriteGameCount()
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetFavoriteGameCount")
	return m_SteamMatchmaking->GetFavoriteGameCount();
}

bool SteamMatchmakingWrapper::GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetFavoriteGame")
	return m_SteamMatchmaking->GetFavoriteGame(iGame, pnAppID, pnIP, pnConnPort, pnQueryPort, punFlags, pRTime32LastPlayedOnServer);
}

int SteamMatchmakingWrapper::AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddFavoriteGame")
	return m_SteamMatchmaking->AddFavoriteGame(nAppID, nIP, nConnPort, nQueryPort, unFlags, rTime32LastPlayedOnServer);
}

bool SteamMatchmakingWrapper::RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
{
	LOG(7, "%s", "SteamMatchmakingWrapper RemoveFavoriteGame")
	return m_SteamMatchmaking->RemoveFavoriteGame(nAppID, nIP, nConnPort, nQueryPort, unFlags);
}

SteamAPICall_t SteamMatchmakingWrapper::RequestLobbyList()
{
	LOG(7, "%s", "SteamMatchmakingWrapper RequestLobbyList")
	return m_SteamMatchmaking->RequestLobbyList();
}

void SteamMatchmakingWrapper::AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListStringFilter")
	return m_SteamMatchmaking->AddRequestLobbyListStringFilter(pchKeyToMatch, pchValueToMatch, eComparisonType);
}

void SteamMatchmakingWrapper::AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListNumericalFilter")
	return m_SteamMatchmaking->AddRequestLobbyListNumericalFilter(pchKeyToMatch, nValueToMatch, eComparisonType);
}
void SteamMatchmakingWrapper::AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListNearValueFilter")
	return m_SteamMatchmaking->AddRequestLobbyListNearValueFilter(pchKeyToMatch, nValueToBeCloseTo);
}
void SteamMatchmakingWrapper::AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListFilterSlotsAvailable")
	return m_SteamMatchmaking->AddRequestLobbyListFilterSlotsAvailable(nSlotsAvailable);
}

void SteamMatchmakingWrapper::AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListDistanceFilter")
	return m_SteamMatchmaking->AddRequestLobbyListDistanceFilter(eLobbyDistanceFilter);
}

void SteamMatchmakingWrapper::AddRequestLobbyListResultCountFilter(int cMaxResults)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListResultCountFilter")
	return m_SteamMatchmaking->AddRequestLobbyListResultCountFilter(cMaxResults);
}

void SteamMatchmakingWrapper::AddRequestLobbyListCompatibleMembersFilter(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper AddRequestLobbyListCompatibleMembersFilter")
	return m_SteamMatchmaking->AddRequestLobbyListCompatibleMembersFilter(steamIDLobby);
}

CSteamID SteamMatchmakingWrapper::GetLobbyByIndex(int iLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyByIndex")
	return m_SteamMatchmaking->GetLobbyByIndex(iLobby);
}

SteamAPICall_t SteamMatchmakingWrapper::CreateLobby(ELobbyType eLobbyType, int cMaxMembers)
{
	LOG(7, "%s", "SteamMatchmakingWrapper CreateLobby")
	return m_SteamMatchmaking->CreateLobby(eLobbyType, cMaxMembers);
}

SteamAPICall_t SteamMatchmakingWrapper::JoinLobby(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper JoinLobby")
	LOG(7, "    - steamIDLobby: %llu", steamIDLobby.ConvertToUint64())
	return m_SteamMatchmaking->JoinLobby(steamIDLobby);
}

void SteamMatchmakingWrapper::LeaveLobby(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper LeaveLobby")
	return m_SteamMatchmaking->LeaveLobby(steamIDLobby);
}

bool SteamMatchmakingWrapper::InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
{
	LOG(7, "%s", "SteamMatchmakingWrapper InviteUserToLobby")
	return m_SteamMatchmaking->InviteUserToLobby(steamIDLobby, steamIDInvitee);
}

int SteamMatchmakingWrapper::GetNumLobbyMembers(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetNumLobbyMembers")
	return m_SteamMatchmaking->GetNumLobbyMembers(steamIDLobby);
}

CSteamID SteamMatchmakingWrapper::GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyMemberByIndex")
	return m_SteamMatchmaking->GetLobbyMemberByIndex(steamIDLobby, iMember);
}

const char* SteamMatchmakingWrapper::GetLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyData")

	const char* ret = m_SteamMatchmaking->GetLobbyData(steamIDLobby, pchKey);

	LOG(7, "    - steamIDLobby: %llu, pchKey: %s, ret: %s", steamIDLobby.ConvertToUint64(), pchKey, ret)

	return ret;
}

bool SteamMatchmakingWrapper::SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyData")
	return m_SteamMatchmaking->SetLobbyData(steamIDLobby, pchKey, pchValue);
}

int SteamMatchmakingWrapper::GetLobbyDataCount(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyDataCount")
	return m_SteamMatchmaking->GetLobbyDataCount(steamIDLobby);
}

bool SteamMatchmakingWrapper::GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyDataByIndex")
	return m_SteamMatchmaking->GetLobbyDataByIndex(steamIDLobby, iLobbyData, pchKey, cchKeyBufferSize, pchValue, cchValueBufferSize);
}

bool SteamMatchmakingWrapper::DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	LOG(7, "%s", "SteamMatchmakingWrapper DeleteLobbyData")
	return m_SteamMatchmaking->DeleteLobbyData(steamIDLobby, pchKey);
}

const char* SteamMatchmakingWrapper::GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyMemberData")
	//DWORD returnAddress = 0;
	//__asm
	//{
	//	push eax
	//	mov eax, [ebp + 4]
	//	mov[returnAddress], eax
	//	pop eax
	//}
	//LOG(7, "\treturn address: 0x%x\n", returnAddress);
	//LOG(7, "\tsteamIDLobby: 0x%x, steamIDUser: 0x%x, pchKey: %s\n", steamIDLobby, steamIDUser, pchKey);

	//opponentPlayer = new CSteamID(steamIDRemote);

	const char* ret = m_SteamMatchmaking->GetLobbyMemberData(steamIDLobby, steamIDUser, pchKey);

	LOG(7, "    - steamIDLobby: %llu, steamIDUser: %llu, pchKey: %s, ret: %s",
		steamIDLobby.ConvertToUint64(), steamIDUser.ConvertToUint64(), pchKey, ret)

	return ret;
}

void SteamMatchmakingWrapper::SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyMemberData")
	return m_SteamMatchmaking->SetLobbyMemberData(steamIDLobby, pchKey, pchValue);
}

bool SteamMatchmakingWrapper::SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SendLobbyChatMsg")
	return m_SteamMatchmaking->SendLobbyChatMsg(steamIDLobby, pvMsgBody, cubMsgBody);
}

int SteamMatchmakingWrapper::GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, OUT_STRUCT() CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyChatEntry")
	return m_SteamMatchmaking->GetLobbyChatEntry(steamIDLobby, iChatID, pSteamIDUser, pvData, cubData, peChatEntryType);
}

bool SteamMatchmakingWrapper::RequestLobbyData(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper RequestLobbyData")
	return m_SteamMatchmaking->RequestLobbyData(steamIDLobby);
}

void SteamMatchmakingWrapper::SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyGameServer")
	return m_SteamMatchmaking->SetLobbyGameServer(steamIDLobby, unGameServerIP, unGameServerPort, steamIDGameServer);
}

bool SteamMatchmakingWrapper::GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, OUT_STRUCT() CSteamID *psteamIDGameServer)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyGameServer")
	return m_SteamMatchmaking->GetLobbyGameServer(steamIDLobby, punGameServerIP, punGameServerPort, psteamIDGameServer);
}

bool SteamMatchmakingWrapper::SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyMemberLimit")
	return m_SteamMatchmaking->SetLobbyMemberLimit(steamIDLobby, cMaxMembers);
}

int SteamMatchmakingWrapper::GetLobbyMemberLimit(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyMemberLimit")
	return m_SteamMatchmaking->GetLobbyMemberLimit(steamIDLobby);
}

bool SteamMatchmakingWrapper::SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyType")
	return m_SteamMatchmaking->SetLobbyType(steamIDLobby, eLobbyType);
}

bool SteamMatchmakingWrapper::SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyJoinable")
	return m_SteamMatchmaking->SetLobbyJoinable(steamIDLobby, bLobbyJoinable);
}

CSteamID SteamMatchmakingWrapper::GetLobbyOwner(CSteamID steamIDLobby)
{
	LOG(7, "%s", "SteamMatchmakingWrapper GetLobbyOwner")
	return m_SteamMatchmaking->GetLobbyOwner(steamIDLobby);
}

bool SteamMatchmakingWrapper::SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLobbyOwner")
	return m_SteamMatchmaking->SetLobbyOwner(steamIDLobby, steamIDNewOwner);
}

bool SteamMatchmakingWrapper::SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobbyDependent)
{
	LOG(7, "%s", "SteamMatchmakingWrapper SetLinkedLobby")
	return m_SteamMatchmaking->SetLinkedLobby(steamIDLobby, steamIDLobbyDependent);
}

#ifdef _PS3
void SteamMatchmakingWrapper::CheckForPSNGameBootInvite(unsigned int iGameBootAttributes)
{
	LOG(7, "%s", "SteamMatchmakingWrapper CheckForPSNGameBootInvite")
	return m_SteamMatchmaking->CheckForPSNGameBootInvite(iGameBootAttributes);
}
#endif