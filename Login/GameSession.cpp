#include "StdAfx.h"

template <> GameSession::HandlerStorageMap BaseSession<GamePacketHandler>::m_handlers;

void GameSession::InitHandlersTable()
{
	m_handlers[CMSG_CONNECT].Handler = &GameSession::HandleConnectMessage;
	m_handlers[CMSG_CONNECT].Flag = FLAG_NOT_CONNECTED;

	m_handlers[CMSG_STATE].Handler = &GameSession::HandleStateMessage;

	m_handlers[CMSG_PLAYERS].Handler = &GameSession::HandlePlayersMessage;
}

void GameSession::HandleStateMessage(ByteBuffer& packet)
{
	uint8 state;
	packet>>state;
	m_server->SetState(state);
	World::Instance().RefreshGameServer(m_server);
}

void GameSession::HandlePlayersMessage(ByteBuffer& packet)
{
	uint16 players;
	packet>>players;
	m_server->SetPlayers(players);
	World::Instance().RefreshGameServer(m_server);
}

void GameSession::HandleConnectMessage(ByteBuffer& packet)
{
	uint16 id;
	std::string key;
	packet>>id>>key;

	GameServer* G = World::Instance().GetGameServer(id);
	if(G == NULL)
		throw ServerError("Undefined server");
	if(G->GetKey() != key)
		throw ServerError("Wrong key");
	if(World::Instance().GetGameSession(id) != NULL)
		throw ServerError("Already connected");

	m_server = G;
}

GameSession::~GameSession()
{
	if(m_server != NULL)
	{
		m_server->SetState(OFFLINE);
		World::Instance().RefreshGameServer(m_server);
	}
}