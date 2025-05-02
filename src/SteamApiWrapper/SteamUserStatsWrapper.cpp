#include "SteamUserStatsWrapper.h"

#include "../logger.h"
#include "Core/utils.h"

SteamUserStatsWrapper::SteamUserStatsWrapper(ISteamUserStats** pSteamUserStats)
{
	LOG(7, "%s", "SteamUserStatsWrapper")
	LOG(7, "    - before: *pSteamUserStats: 0x%p, thispointer: 0x%p\n", *pSteamUserStats, this);

	m_SteamUserStats = *pSteamUserStats;
	void* thisAddress = this;
	WriteToProtectedMemory((uintptr_t)pSteamUserStats, (char*)&thisAddress, 4); //basically *pSteamUserStats = this;

	LOG(7, "    - after: *pSteamUserStats: 0x%p, m_SteamUserStats: 0x%p\n", *pSteamUserStats, m_SteamUserStats);
}

SteamUserStatsWrapper::~SteamUserStatsWrapper()
{
}

CALL_BACK(UserStatsReceived_t)
bool SteamUserStatsWrapper::RequestCurrentStats()
{
	LOG(7, "%s", "RequestCurrentStats")
	return m_SteamUserStats->RequestCurrentStats();
}

bool SteamUserStatsWrapper::GetStat(const char *pchName, int32 *pData)
{
	LOG(7, "%s", "GetStat")
	return m_SteamUserStats->GetStat(pchName, pData);
}

bool SteamUserStatsWrapper::GetStat(const char *pchName, float *pData)
{
	LOG(7, "%s", "GetStat")
	return m_SteamUserStats->GetStat(pchName, pData);
}

bool SteamUserStatsWrapper::SetStat(const char *pchName, int32 nData)
{
	LOG(7, "%s", "SetStat")
	return m_SteamUserStats->SetStat(pchName, nData);
}

bool SteamUserStatsWrapper::SetStat(const char *pchName, float fData)
{
	LOG(7, "%s", "SetStat")
	return m_SteamUserStats->SetStat(pchName, fData);
}

bool SteamUserStatsWrapper::UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength)
{
	LOG(7, "%s", "UpdateAvgRateStat")
	return m_SteamUserStats->UpdateAvgRateStat(pchName, flCountThisSession, dSessionLength);
}

bool SteamUserStatsWrapper::GetAchievement(const char *pchName, bool *pbAchieved)
{
	LOG(7, "%s", "GetAchievement")
	return m_SteamUserStats->GetAchievement(pchName, pbAchieved);
}

bool SteamUserStatsWrapper::SetAchievement(const char *pchName)
{
	LOG(7, "%s", "SetAchievement")
	return m_SteamUserStats->SetAchievement(pchName);
}

bool SteamUserStatsWrapper::ClearAchievement(const char *pchName)
{
	LOG(7, "%s", "ClearAchievement")
	return m_SteamUserStats->ClearAchievement(pchName);
}

bool SteamUserStatsWrapper::GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
{
	LOG(7, "%s", "GetAchievementAndUnlockTime")
	return m_SteamUserStats->GetAchievementAndUnlockTime(pchName, pbAchieved, punUnlockTime);
}

bool SteamUserStatsWrapper::StoreStats()
{
	LOG(7, "%s", "StoreStats")
	return m_SteamUserStats->StoreStats();
}

int SteamUserStatsWrapper::GetAchievementIcon(const char *pchName)
{
	LOG(7, "%s", "GetAchievementIcon")
	return m_SteamUserStats->GetAchievementIcon(pchName);
}

const char *SteamUserStatsWrapper::GetAchievementDisplayAttribute(const char *pchName, const char *pchKey)
{
	LOG(7, "%s", "GetAchievementDisplayAttribute")
	return m_SteamUserStats->GetAchievementDisplayAttribute(pchName, pchKey);
}

bool SteamUserStatsWrapper::IndicateAchievementProgress(const char *pchName, uint32 nCurProgress, uint32 nMaxProgress)
{
	LOG(7, "%s", "IndicateAchievementProgress")
	return m_SteamUserStats->IndicateAchievementProgress(pchName, nCurProgress, nMaxProgress);
}

uint32 SteamUserStatsWrapper::GetNumAchievements()
{
	LOG(7, "%s", "GetNumAchievements")
	return m_SteamUserStats->GetNumAchievements();
}

const char *SteamUserStatsWrapper::GetAchievementName(uint32 iAchievement)
{
	LOG(7, "%s", "GetAchievementName")
	return m_SteamUserStats->GetAchievementName(iAchievement);
}

CALL_RESULT(UserStatsReceived_t)
SteamAPICall_t SteamUserStatsWrapper::RequestUserStats(CSteamID steamIDUser)
{
	LOG(7, "%s", "RequestUserStats")
	return m_SteamUserStats->RequestUserStats(steamIDUser);
}

bool SteamUserStatsWrapper::GetUserStat(CSteamID steamIDUser, const char *pchName, int32 *pData)
{
	LOG(7, "%s", "GetUserStat")
	return m_SteamUserStats->GetUserStat(steamIDUser, pchName, pData);
}

bool SteamUserStatsWrapper::GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData)
{
	LOG(7, "%s", "GetUserStat")
	return m_SteamUserStats->GetUserStat(steamIDUser, pchName, pData);
}

bool SteamUserStatsWrapper::GetUserAchievement(CSteamID steamIDUser, const char *pchName, bool *pbAchieved)
{
	LOG(7, "%s", "GetUserAchievement")
	return m_SteamUserStats->GetUserAchievement(steamIDUser, pchName, pbAchieved);
}

bool SteamUserStatsWrapper::GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
{
	LOG(7, "%s", "GetUserAchievementAndUnlockTime")
	return m_SteamUserStats->GetUserAchievementAndUnlockTime(steamIDUser, pchName, pbAchieved, punUnlockTime);
}

bool SteamUserStatsWrapper::ResetAllStats(bool bAchievementsToo)
{
	LOG(7, "%s", "ResetAllStats")
	return m_SteamUserStats->ResetAllStats(bAchievementsToo);
}

CALL_RESULT(LeaderboardFindResult_t)
SteamAPICall_t SteamUserStatsWrapper::FindOrCreateLeaderboard(const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
{
	LOG(7, "%s", "FindOrCreateLeaderboard")
	return m_SteamUserStats->FindOrCreateLeaderboard(pchLeaderboardName, eLeaderboardSortMethod, eLeaderboardDisplayType);
}

CALL_RESULT(LeaderboardFindResult_t)
SteamAPICall_t SteamUserStatsWrapper::FindLeaderboard(const char *pchLeaderboardName)
{
	LOG(7, "%s", "FindLeaderboard")
	return m_SteamUserStats->FindLeaderboard(pchLeaderboardName);
}

const char *SteamUserStatsWrapper::GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
{
	LOG(7, "%s", "GetLeaderboardName")
	return m_SteamUserStats->GetLeaderboardName(hSteamLeaderboard);
}

int SteamUserStatsWrapper::GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
{
	LOG(7, "%s", "GetLeaderboardEntryCount")
	return m_SteamUserStats->GetLeaderboardEntryCount(hSteamLeaderboard);
}

ELeaderboardSortMethod SteamUserStatsWrapper::GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard)
{
	LOG(7, "%s", "GetLeaderboardSortMethod")
	return m_SteamUserStats->GetLeaderboardSortMethod(hSteamLeaderboard);
}

ELeaderboardDisplayType SteamUserStatsWrapper::GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard)
{
	LOG(7, "%s", "GetLeaderboardDisplayType")
	return m_SteamUserStats->GetLeaderboardDisplayType(hSteamLeaderboard);
}

CALL_RESULT(LeaderboardScoresDownloaded_t)
SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
{
	LOG(7, "%s", "DownloadLeaderboardEntries")
	return m_SteamUserStats->DownloadLeaderboardEntries(hSteamLeaderboard, eLeaderboardDataRequest, nRangeStart, nRangeEnd);
}

METHOD_DESC(Downloads leaderboard entries for an arbitrary set of users - ELeaderboardDataRequest is k_ELeaderboardDataRequestUsers)
CALL_RESULT(LeaderboardScoresDownloaded_t)
SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard,
	ARRAY_COUNT_D(cUsers, Array of users to retrieve) CSteamID *prgUsers, int cUsers)
{
	LOG(7, "%s", "DownloadLeaderboardEntriesForUsers")
	return m_SteamUserStats->DownloadLeaderboardEntriesForUsers(hSteamLeaderboard, ARRAY_COUNT_D(cUsers, Array of users to retrieve) prgUsers, cUsers);
}

bool SteamUserStatsWrapper::GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
{
	LOG(7, "%s", "GetDownloadedLeaderboardEntry")
	return m_SteamUserStats->GetDownloadedLeaderboardEntry(hSteamLeaderboardEntries, index, pLeaderboardEntry, pDetails, cDetailsMax);
}

CALL_RESULT(LeaderboardScoreUploaded_t)
SteamAPICall_t SteamUserStatsWrapper::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount)
{
	LOG(7, "%s", "UploadLeaderboardScore")
	return m_SteamUserStats->UploadLeaderboardScore(hSteamLeaderboard, eLeaderboardUploadScoreMethod, nScore, pScoreDetails, cScoreDetailsCount);
}

CALL_RESULT(LeaderboardUGCSet_t)
SteamAPICall_t SteamUserStatsWrapper::AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
{
	LOG(7, "%s", "AttachLeaderboardUGC")
	return m_SteamUserStats->AttachLeaderboardUGC(hSteamLeaderboard, hUGC);
}

CALL_RESULT(NumberOfCurrentPlayers_t)
SteamAPICall_t SteamUserStatsWrapper::GetNumberOfCurrentPlayers()
{
	LOG(7, "%s", "GetNumberOfCurrentPlayers")
	return m_SteamUserStats->GetNumberOfCurrentPlayers();
}

CALL_RESULT(GlobalAchievementPercentagesReady_t)
SteamAPICall_t SteamUserStatsWrapper::RequestGlobalAchievementPercentages()
{
	LOG(7, "%s", "RequestGlobalAchievementPercentages")
	return m_SteamUserStats->RequestGlobalAchievementPercentages();
}

int SteamUserStatsWrapper::GetMostAchievedAchievementInfo(char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	LOG(7, "%s", "GetMostAchievedAchievementInfo")
	return m_SteamUserStats->GetMostAchievedAchievementInfo(pchName, unNameBufLen, pflPercent, pbAchieved);
}

int SteamUserStatsWrapper::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	LOG(7, "%s", "GetNextMostAchievedAchievementInfo")
	return m_SteamUserStats->GetNextMostAchievedAchievementInfo(iIteratorPrevious, pchName, unNameBufLen, pflPercent, pbAchieved);
}

bool SteamUserStatsWrapper::GetAchievementAchievedPercent(const char *pchName, float *pflPercent)
{
	LOG(7, "%s", "GetAchievementAchievedPercent")
	return m_SteamUserStats->GetAchievementAchievedPercent(pchName, pflPercent);
}

CALL_RESULT(GlobalStatsReceived_t)
SteamAPICall_t SteamUserStatsWrapper::RequestGlobalStats(int nHistoryDays)
{
	LOG(7, "%s", "RequestGlobalStats")
	return m_SteamUserStats->RequestGlobalStats(nHistoryDays);
}

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, int64 *pData)
{
	LOG(7, "%s", "GetGlobalStat")
	return m_SteamUserStats->GetGlobalStat(pchStatName, pData);
}

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, double *pData)
{
	LOG(7, "%s", "GetGlobalStat")
	return m_SteamUserStats->GetGlobalStat(pchStatName, pData);
}

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, ARRAY_COUNT(cubData) int64 *pData, uint32 cubData)
{
	LOG(7, "%s", "GetGlobalStatHistory")
	return m_SteamUserStats->GetGlobalStatHistory(pchStatName, ARRAY_COUNT(cubData) pData, cubData);
}

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, ARRAY_COUNT(cubData) double *pData, uint32 cubData)
{
	LOG(7, "%s", "GetGlobalStatHistory")
	return m_SteamUserStats->GetGlobalStatHistory(pchStatName, ARRAY_COUNT(cubData) pData, cubData);
}
