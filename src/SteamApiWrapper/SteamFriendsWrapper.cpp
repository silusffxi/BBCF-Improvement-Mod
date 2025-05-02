#include "../logger.h"
#include "Core/utils.h"
#include "SteamFriendsWrapper.h"

SteamFriendsWrapper::SteamFriendsWrapper(ISteamFriends** pSteamFriends)
{
	LOG(7, "%s", "SteamFriendsWrapper")
	LOG(7, "    - before: *pSteamFriends: 0x%p, thispointer: 0x%p", *pSteamFriends, this)

	m_SteamFriends = *pSteamFriends;
	void* thisAddress = this;
	WriteToProtectedMemory((uintptr_t)pSteamFriends, (char*)&thisAddress, 4); //basically *pSteamFriends = this;

	LOG(7, "    - after: *pSteamFriends: 0x%p, m_SteamFriends: 0x%p", *pSteamFriends, m_SteamFriends)
}

SteamFriendsWrapper::~SteamFriendsWrapper()
{
}

const char *SteamFriendsWrapper::GetPersonaName()
{
	LOG(7, "%s", "GetPersonaName")
	return m_SteamFriends->GetPersonaName();
}

CALL_RESULT(SetPersonaNameResponse_t)
SteamAPICall_t SteamFriendsWrapper::SetPersonaName(const char *pchPersonaName)
{
	LOG(7, "%s", "SetPersonaName")
	return m_SteamFriends->SetPersonaName(pchPersonaName);
}

EPersonaState SteamFriendsWrapper::GetPersonaState()
{
	LOG(7, "%s", "GetPersonaState")
	return m_SteamFriends->GetPersonaState();
}

int SteamFriendsWrapper::GetFriendCount(int iFriendFlags)
{
	LOG(7, "%s", "GetFriendCount")
	return m_SteamFriends->GetFriendCount(iFriendFlags);
}

CSteamID SteamFriendsWrapper::GetFriendByIndex(int iFriend, int iFriendFlags)
{
	LOG(7, "%s", "GetFriendByIndex")
	return m_SteamFriends->GetFriendByIndex(iFriend, iFriendFlags);
}

EFriendRelationship SteamFriendsWrapper::GetFriendRelationship(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendRelationship")
	return m_SteamFriends->GetFriendRelationship(steamIDFriend);
}

EPersonaState SteamFriendsWrapper::GetFriendPersonaState(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendPersonaState")
	return m_SteamFriends->GetFriendPersonaState(steamIDFriend);
}

const char *SteamFriendsWrapper::GetFriendPersonaName(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendPersonaName")
	return m_SteamFriends->GetFriendPersonaName(steamIDFriend);
}

bool SteamFriendsWrapper::GetFriendGamePlayed(CSteamID steamIDFriend, OUT_STRUCT() FriendGameInfo_t *pFriendGameInfo)
{
	LOG(7, "%s", "GetFriendGamePlayed")
	return m_SteamFriends->GetFriendGamePlayed(steamIDFriend, OUT_STRUCT() pFriendGameInfo);
}

const char *SteamFriendsWrapper::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
{
	LOG(7, "%s", "GetFriendPersonaNameHistory")
	return m_SteamFriends->GetFriendPersonaNameHistory(steamIDFriend, iPersonaName);
}

int SteamFriendsWrapper::GetFriendSteamLevel(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendSteamLevel")
	return m_SteamFriends->GetFriendSteamLevel(steamIDFriend);
}

const char *SteamFriendsWrapper::GetPlayerNickname(CSteamID steamIDPlayer)
{
	LOG(7, "%s", "GetPlayerNickname")
	return m_SteamFriends->GetPlayerNickname(steamIDPlayer);
}

int SteamFriendsWrapper::GetFriendsGroupCount()
{
	LOG(7, "%s", "GetFriendsGroupCount")
	return m_SteamFriends->GetFriendsGroupCount();
}

FriendsGroupID_t SteamFriendsWrapper::GetFriendsGroupIDByIndex(int iFG)
{
	LOG(7, "%s", "GetFriendsGroupIDByIndex")
	return m_SteamFriends->GetFriendsGroupIDByIndex(iFG);
}

const char *SteamFriendsWrapper::GetFriendsGroupName(FriendsGroupID_t friendsGroupID)
{
	LOG(7, "%s", "GetFriendsGroupName")
	return m_SteamFriends->GetFriendsGroupName(friendsGroupID);
}

int SteamFriendsWrapper::GetFriendsGroupMembersCount(FriendsGroupID_t friendsGroupID)
{
	LOG(7, "%s", "GetFriendsGroupMembersCount")
	return m_SteamFriends->GetFriendsGroupMembersCount(friendsGroupID);
}

void SteamFriendsWrapper::GetFriendsGroupMembersList(FriendsGroupID_t friendsGroupID, 
	OUT_ARRAY_CALL(nMembersCount, GetFriendsGroupMembersCount, friendsGroupID) CSteamID *pOutSteamIDMembers, int nMembersCount)
{
	LOG(7, "%s", "GetFriendsGroupMembersList")
	return m_SteamFriends->GetFriendsGroupMembersList(friendsGroupID, OUT_ARRAY_CALL(nMembersCount, GetFriendsGroupMembersCount, friendsGroupID) pOutSteamIDMembers, nMembersCount);
}

bool SteamFriendsWrapper::HasFriend(CSteamID steamIDFriend, int iFriendFlags)
{
	LOG(7, "%s", "HasFriend")
	return m_SteamFriends->HasFriend(steamIDFriend, iFriendFlags);
}

int SteamFriendsWrapper::GetClanCount()
{
	LOG(7, "%s", "GetClanCount")
	return m_SteamFriends->GetClanCount();
}

CSteamID SteamFriendsWrapper::GetClanByIndex(int iClan)
{
	LOG(7, "%s", "GetClanByIndex")
	return m_SteamFriends->GetClanByIndex(iClan);
}

const char *SteamFriendsWrapper::GetClanName(CSteamID steamIDClan)
{
	LOG(7, "%s", "GetClanName")
	return m_SteamFriends->GetClanName(steamIDClan);
}

const char *SteamFriendsWrapper::GetClanTag(CSteamID steamIDClan)
{
	LOG(7, "%s", "GetClanTag")
	return m_SteamFriends->GetClanTag(steamIDClan);
}

bool SteamFriendsWrapper::GetClanActivityCounts(CSteamID steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting)
{
	LOG(7, "%s", "GetClanActivityCounts")
	return m_SteamFriends->GetClanActivityCounts(steamIDClan, pnOnline, pnInGame, pnChatting);
}

SteamAPICall_t SteamFriendsWrapper::DownloadClanActivityCounts(ARRAY_COUNT(cClansToRequest) CSteamID *psteamIDClans, int cClansToRequest)
{
	LOG(7, "%s", "DownloadClanActivityCounts")
	return m_SteamFriends->DownloadClanActivityCounts(ARRAY_COUNT(cClansToRequest) psteamIDClans, cClansToRequest);
}

int SteamFriendsWrapper::GetFriendCountFromSource(CSteamID steamIDSource)
{
	LOG(7, "%s", "GetFriendCountFromSource")
	return m_SteamFriends->GetFriendCountFromSource(steamIDSource);
}

CSteamID SteamFriendsWrapper::GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend)
{
	LOG(7, "%s", "GetFriendFromSourceByIndex")
	return m_SteamFriends->GetFriendFromSourceByIndex(steamIDSource, iFriend);
}

bool SteamFriendsWrapper::IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
{
	LOG(7, "%s", "IsUserInSource")
	return m_SteamFriends->IsUserInSource(steamIDUser, steamIDSource);
}

void SteamFriendsWrapper::SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
{
	LOG(7, "%s", "SetInGameVoiceSpeaking")
	return m_SteamFriends->SetInGameVoiceSpeaking(steamIDUser, bSpeaking);
}

void SteamFriendsWrapper::ActivateGameOverlay(const char *pchDialog)
{
	LOG(7, "%s", "ActivateGameOverlay")
	return m_SteamFriends->ActivateGameOverlay(pchDialog);
}

void SteamFriendsWrapper::ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID)
{
	LOG(7, "%s", "ActivateGameOverlayToUser")
	return m_SteamFriends->ActivateGameOverlayToUser(pchDialog, steamID);
}

void SteamFriendsWrapper::ActivateGameOverlayToWebPage(const char *pchURL)
{
	LOG(7, "%s", "ActivateGameOverlayToWebPage")
	return m_SteamFriends->ActivateGameOverlayToWebPage(pchURL);
}

void SteamFriendsWrapper::ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag)
{
	LOG(7, "%s", "ActivateGameOverlayToStore")
	return m_SteamFriends->ActivateGameOverlayToStore(nAppID, eFlag);
}

void SteamFriendsWrapper::SetPlayedWith(CSteamID steamIDUserPlayedWith)
{
	LOG(2, "%s", "SetPlayedWith")
	return m_SteamFriends->SetPlayedWith(steamIDUserPlayedWith);
}

void SteamFriendsWrapper::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
{
	LOG(7, "%s", "ActivateGameOverlayInviteDialog")
	return m_SteamFriends->ActivateGameOverlayInviteDialog(steamIDLobby);
}

int SteamFriendsWrapper::GetSmallFriendAvatar(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetSmallFriendAvatar")
	return m_SteamFriends->GetSmallFriendAvatar(steamIDFriend);
}

int SteamFriendsWrapper::GetMediumFriendAvatar(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetMediumFriendAvatar")
	return m_SteamFriends->GetMediumFriendAvatar(steamIDFriend);
}

int SteamFriendsWrapper::GetLargeFriendAvatar(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetLargeFriendAvatar")
	return m_SteamFriends->GetLargeFriendAvatar(steamIDFriend);
}

bool SteamFriendsWrapper::RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly)
{
	LOG(7, "%s", "RequestUserInformation")
	return m_SteamFriends->RequestUserInformation(steamIDUser, bRequireNameOnly);
}

CALL_RESULT(ClanOfficerListResponse_t)
SteamAPICall_t SteamFriendsWrapper::RequestClanOfficerList(CSteamID steamIDClan)
{
	LOG(7, "%s", "RequestClanOfficerList")
	return m_SteamFriends->RequestClanOfficerList(steamIDClan);
}

CSteamID SteamFriendsWrapper::GetClanOwner(CSteamID steamIDClan)
{
	LOG(7, "%s", "GetClanOwner")
	return m_SteamFriends->GetClanOwner(steamIDClan);
}

int SteamFriendsWrapper::GetClanOfficerCount(CSteamID steamIDClan)
{
	LOG(7, "%s", "GetClanOfficerCount")
	return m_SteamFriends->GetClanOfficerCount(steamIDClan);
}

CSteamID SteamFriendsWrapper::GetClanOfficerByIndex(CSteamID steamIDClan, int iOfficer)
{
	LOG(7, "%s", "GetClanOfficerByIndex")
	return m_SteamFriends->GetClanOfficerByIndex(steamIDClan, iOfficer);
}

uint32 SteamFriendsWrapper::GetUserRestrictions()
{
	LOG(7, "%s", "GetUserRestrictions")
	return m_SteamFriends->GetUserRestrictions();
}

bool SteamFriendsWrapper::SetRichPresence(const char *pchKey, const char *pchValue)
{
	LOG(7, "%s", "SetRichPresence")
	return m_SteamFriends->SetRichPresence(pchKey, pchValue);
}

void SteamFriendsWrapper::ClearRichPresence()
{
	LOG(7, "%s", "ClearRichPresence")
	return m_SteamFriends->ClearRichPresence();
}

const char *SteamFriendsWrapper::GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey)
{
	LOG(7, "%s", "GetFriendRichPresence")
	return m_SteamFriends->GetFriendRichPresence(steamIDFriend, pchKey);
}

int SteamFriendsWrapper::GetFriendRichPresenceKeyCount(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendRichPresenceKeyCount")
	return m_SteamFriends->GetFriendRichPresenceKeyCount(steamIDFriend);
}

const char *SteamFriendsWrapper::GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey)
{
	LOG(7, "%s", "GetFriendRichPresenceKeyByIndex")
	return m_SteamFriends->GetFriendRichPresenceKeyByIndex(steamIDFriend, iKey);
}

void SteamFriendsWrapper::RequestFriendRichPresence(CSteamID steamIDFriend)
{
	LOG(7, "%s", "RequestFriendRichPresence")
	return m_SteamFriends->RequestFriendRichPresence(steamIDFriend);
}

bool SteamFriendsWrapper::InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString)
{
	LOG(7, "%s", "InviteUserToGame")
	return m_SteamFriends->InviteUserToGame(steamIDFriend, pchConnectString);
}

int SteamFriendsWrapper::GetCoplayFriendCount()
{
	LOG(7, "%s", "GetCoplayFriendCount")
	return m_SteamFriends->GetCoplayFriendCount();
}

CSteamID SteamFriendsWrapper::GetCoplayFriend(int iCoplayFriend)
{
	LOG(7, "%s", "GetCoplayFriend")
	return m_SteamFriends->GetCoplayFriend(iCoplayFriend);
}

int SteamFriendsWrapper::GetFriendCoplayTime(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendCoplayTime")
	return m_SteamFriends->GetFriendCoplayTime(steamIDFriend);
}

AppId_t SteamFriendsWrapper::GetFriendCoplayGame(CSteamID steamIDFriend)
{
	LOG(7, "%s", "GetFriendCoplayGame")
	return m_SteamFriends->GetFriendCoplayGame(steamIDFriend);
}

// chat interface for games
// this allows in-game access to group (clan) chats from in the game
// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
CALL_RESULT(JoinClanChatRoomCompletionResult_t)
SteamAPICall_t SteamFriendsWrapper::JoinClanChatRoom(CSteamID steamIDClan)
{
	LOG(7, "%s", "JoinClanChatRoom")
	return m_SteamFriends->JoinClanChatRoom(steamIDClan);
}

bool SteamFriendsWrapper::LeaveClanChatRoom(CSteamID steamIDClan)
{
	LOG(7, "%s", "LeaveClanChatRoom")
	return m_SteamFriends->LeaveClanChatRoom(steamIDClan);
}

int SteamFriendsWrapper::GetClanChatMemberCount(CSteamID steamIDClan)
{
	LOG(7, "%s", "GetClanChatMemberCount")
	return m_SteamFriends->GetClanChatMemberCount(steamIDClan);
}

CSteamID SteamFriendsWrapper::GetChatMemberByIndex(CSteamID steamIDClan, int iUser)
{
	LOG(7, "%s", "GetChatMemberByIndex")
    return m_SteamFriends->GetChatMemberByIndex(steamIDClan, iUser);
}

bool SteamFriendsWrapper::SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText)
{
	LOG(7, "%s", "SendClanChatMessage")
	return m_SteamFriends->SendClanChatMessage(steamIDClanChat, pchText);
}

int SteamFriendsWrapper::GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, OUT_STRUCT() CSteamID *psteamidChatter)
{
	LOG(7, "%s", "GetClanChatMessage")
	return m_SteamFriends->GetClanChatMessage(steamIDClanChat, iMessage, prgchText, cchTextMax, peChatEntryType, OUT_STRUCT() psteamidChatter);
}

bool SteamFriendsWrapper::IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser)
{
	LOG(7, "%s", "IsClanChatAdmin")
	return m_SteamFriends->IsClanChatAdmin(steamIDClanChat, steamIDUser);
}

bool SteamFriendsWrapper::IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat)
{
	LOG(7, "%s", "IsClanChatWindowOpenInSteam")
	return m_SteamFriends->IsClanChatWindowOpenInSteam(steamIDClanChat);
}

bool SteamFriendsWrapper::OpenClanChatWindowInSteam(CSteamID steamIDClanChat)
{
	LOG(7, "%s", "OpenClanChatWindowInSteam")
	return m_SteamFriends->OpenClanChatWindowInSteam(steamIDClanChat);
}

bool SteamFriendsWrapper::CloseClanChatWindowInSteam(CSteamID steamIDClanChat)
{
	LOG(7, "%s", "CloseClanChatWindowInSteam")
	return m_SteamFriends->CloseClanChatWindowInSteam(steamIDClanChat);
}

// peer-to-peer chat interception
// this is so you can show P2P chats inline in the game
bool SteamFriendsWrapper::SetListenForFriendsMessages(bool bInterceptEnabled)
{
	LOG(7, "%s", "SetListenForFriendsMessages")
	return m_SteamFriends->SetListenForFriendsMessages(bInterceptEnabled);
}

bool SteamFriendsWrapper::ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend)
{
	LOG(7, "%s", "ReplyToFriendMessage")
	return m_SteamFriends->ReplyToFriendMessage(steamIDFriend, pchMsgToSend);
}

int SteamFriendsWrapper::GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	LOG(7, "%s", "GetFriendMessage")
	return m_SteamFriends->GetFriendMessage(steamIDFriend, iMessageID, pvData, cubData, peChatEntryType);
}

CALL_RESULT(FriendsGetFollowerCount_t)
SteamAPICall_t SteamFriendsWrapper::GetFollowerCount(CSteamID steamID)
{
	LOG(7, "%s", "GetFollowerCount")
	return m_SteamFriends->GetFollowerCount(steamID);
}

CALL_RESULT(FriendsIsFollowing_t)
SteamAPICall_t SteamFriendsWrapper::IsFollowing(CSteamID steamID)
{
	LOG(7, "%s", "IsFollowing")
	return m_SteamFriends->IsFollowing(steamID);
}

CALL_RESULT(FriendsEnumerateFollowingList_t)
SteamAPICall_t SteamFriendsWrapper::EnumerateFollowingList(uint32 unStartIndex)
{
	LOG(7, "%s", "EnumerateFollowingList")
	return m_SteamFriends->EnumerateFollowingList(unStartIndex);
}
