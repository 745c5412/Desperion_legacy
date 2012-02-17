/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

    Desperion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Desperion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"

template <> GameSession::HandlerStorageMap AbstractSession<GamePacketHandler>::m_handlers;

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

void GameSession::SendDisconnectPlayerMessage(int account)
{
	ByteBuffer dest, src;
	src<<account;
	Packet::Pack(SMSG_DISCONNECT_PLAYER, dest, src);
	_Send(dest);
}

void GameSession::HandlePlayersMessage(ByteBuffer& packet)
{
	uint16 players;
	packet>>players;
	m_server->SetPlayers(players);
	Desperion::Master::Instance().GetService().post(
			boost::bind(&World::RefreshGameServer, World::InstancePtr(), m_server));
}

void GameSession::HandleConnectMessage(ByteBuffer& packet)
{
	uint16 id;
	std::string key;
	packet>>id>>key;

	GameServer* G = World::Instance().GetGameServer(id);
	if(G == NULL || G->GetKey() != key || World::Instance().GetGameSession(id) != NULL)
	{
		CloseSocket();
		return;
	}

	m_server = G;
	World::Instance().AddGameSession(this);
}

GameSession::~GameSession()
{
	if(m_server != NULL)
	{
		m_server->SetState(OFFLINE);
		Desperion::Master::Instance().GetService().post(
			boost::bind(&World::RefreshGameServer, World::InstancePtr(), m_server));
		World::Instance().DeleteGameSession(m_server->GetID());
	}
}