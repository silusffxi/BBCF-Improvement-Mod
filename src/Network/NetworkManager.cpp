#include "NetworkManager.h"
#include "RoomManager.h"
#include "Core/interfaces.h"
#include "Core/utils.h"
#include "Game/gamestates.h"
#include "Overlay/Logger/ImGuiLogger.h"
#include "../logger.h"

NetworkManager::NetworkManager(SteamNetworkingWrapper* SteamNetworking, CSteamID steamID)
{
	m_pSteamNetworking = SteamNetworking;
	m_steamID = steamID;
}

NetworkManager::~NetworkManager()
{
}

bool NetworkManager::SendPacket(CSteamID* steamID, Packet* packet)
{
	LOG(2, "%s", "NetworkManager::SendPacket")

	packet->steamID = m_steamID.ConvertToUint64();

	LOG(2, "%s", "    Sending packet:")
	LOG(2, "    version: %s", RawMemoryArrayToString((unsigned char*)&packet->version, sizeof(packet->version)))
	LOG(2, "    packetType: %s", RawMemoryArrayToString((unsigned char*)&packet->packetType, sizeof(packet->packetType)))
	LOG(2, "    part: %s", RawMemoryArrayToString((unsigned char*)&packet->part, sizeof(packet->part)))
	LOG(2, "    packetSize: %s", RawMemoryArrayToString((unsigned char*)&packet->packetSize, sizeof(packet->packetSize)))
	LOG(2, "    roomPlayerIndex: %s", RawMemoryArrayToString((unsigned char*)&packet->roomMemberIndex, sizeof(packet->roomMemberIndex)))
	LOG(2, "    steamID: %s", RawMemoryArrayToString((unsigned char*)&packet->steamID, sizeof(packet->steamID)))
	LOG(2, "    dataSize: %s", RawMemoryArrayToString((unsigned char*)&packet->dataSize, sizeof(packet->dataSize)))
	//LOG(2, "\tdata: %s\n", RawMemoryArrayToString((unsigned char*)&packet->data, sizeof(packet->data)));

	EP2PSend sendType = k_EP2PSendUnreliable;

	return m_pSteamNetworking->SendP2PPacket(*steamID, packet, packet->packetSize, sendType, 0);
}

void NetworkManager::RecvPacket(Packet* packet)
{
	LOG(7, "%s", "NetworkManager::RecvPacket")

	if (!g_interfaces.pRoomManager->IsPacketFromSameRoom(packet))
	{
		LOG(2, "[error] Packet received from not a room member. RoomPlayerIndex: %d, SteamID: %llu",
			packet->roomMemberIndex, packet->steamID)

		return;
	}

	switch (packet->packetType)
	{
	case PacketType_IMID_Announce:
		g_interfaces.pRoomManager->SendAcknowledge(packet);
		break;

	case PacketType_IMID_Acknowledge:
		g_interfaces.pRoomManager->AcceptAcknowledge(packet);
		break;

	case PacketType_PaletteInfo:
		if (g_interfaces.pRoomManager->IsPacketFromSameMatchNonSpectator(packet))
		{
			g_interfaces.pOnlinePaletteManager->RecvPaletteInfoPacket(packet);
		}
		break;

	case PacketType_PaletteData:
		if (g_interfaces.pRoomManager->IsPacketFromSameMatchNonSpectator(packet))
		{
			g_interfaces.pOnlinePaletteManager->RecvPaletteDataPacket(packet);
		}
		break;

	case PacketType_GameMode:
		if (g_interfaces.pRoomManager->IsPacketFromSameMatchNonSpectator(packet) &&
			*g_gameVals.pGameState == GameState_CharacterSelectionScreen)
		{
			g_interfaces.pOnlineGameModeManager->RecvGameModePacket(packet);
		}
		break;

	case PacketType_UploadReplayEnabled_Broadcast:
		//this packet will signal if either p1 or p2 in the match does not want to have the replay uploaded. Spectators won't send these broadcasts.
		LOG(2, "%s", "RECEIVED PACKET PacketType_UploadReplayEnabled_Broadcast")
		int allowUpload;
		memcpy(&allowUpload, packet->data, packet->dataSize);
		g_imGuiLogger->Log("Received PacketType_UploadReplayEnabled_Broadcast. \n\tdata: '%d'\n\t steamid: '%d'\n",
			allowUpload,
			packet->steamID
			);
		if (g_interfaces.pRoomManager->IsPacketFromSameMatchNonSpectator(packet)) 
		{
			g_interfaces.pReplayUploadManager->RecvReplayUploadEnabledBroadcastPacket(packet);
		}
		break;

	default:
		LOG(2, "Unknown packet type received: %d", packet->packetType)
		g_imGuiLogger->Log("[error] Unknown packet type received (%d)\n", packet->packetType);
	}
}

bool NetworkManager::IsIMPacket(Packet* packet)
{
	return packet->version == IM_PACKET_VERSION;
}