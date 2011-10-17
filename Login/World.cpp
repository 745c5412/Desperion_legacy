/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

template <> World * Singleton<World>::m_singleton = NULL;

World::World()
{
	m_maxPlayers = 0;
}

void World::RefreshGameServer(GameServer* G)
{
	SessionsMutex.lock();
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		uint32 guid = it->second->GetData(FLAG_GUID).intValue;
		if(guid == 0)
			continue;
		QueryResult* QR = Desperion::sDatabase->Query("SELECT count FROM character_counts WHERE accountGuid=%u and serverID=%u LIMIT 1;",
			guid, G->GetID());
		uint8 count;
		if(QR)
		{
			Field* fields = QR->Fetch();
			count = fields[0].GetUInt8();
		}
		delete QR;

		it->second->Send(ServerStatusUpdateMessage(it->second->GetServerStatusMessage(G, count)));
	}
	SessionsMutex.unlock();
}

World::~World()
{
	Sessions.clear();
	GameSessions.clear();

	for(GameServerMap::iterator it = GameServers.begin(); it != GameServers.end(); ++it)
		delete it->second;
	GameServers.clear();
}

void World::LoadGameServers()
{
	const char * query = "SELECT * FROM game_servers;";
	QueryResult* QR = Desperion::sDatabase->Query(query);
	if(!QR)
		return;
	do
	{
		Field * fields = QR->Fetch();
		uint16 id = fields[0].GetUInt16();
		GameServer* g = new GameServer;
		g->Init(id, fields[1].GetString(), fields[2].GetUInt16(), fields[3].GetUInt8(), fields[5].GetString(), fields[4].GetUInt16(), fields[6].GetUInt8());
		GameServers[id] = g;
	}while(QR->NextRow());
	delete QR;
	Log::Instance().outNotice("World", "%u game servers loaded!", GameServers.size());
}

void World::Init()
{
	Log::Instance().outNotice("World", "Loading world...");
	LoadGameServers();

	Session::InitHandlersTable();
	GameSession::InitHandlersTable();
	Log::Instance().outNotice("World", "World loaded!\n\n");
}

void World::AddSession(Session* s)
{
	SessionsMutex.lock();
	Sessions[s->GetData(FLAG_GUID).intValue] = s;
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
	SessionsMutex.unlock();
}

Session* World::GetSession(int guid)
{
	Session* s = NULL;
	SessionsMutex.lock();
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		s = it->second;
	SessionsMutex.unlock();
	return s;
}

void World::DeleteSession(int guid)
{
	SessionsMutex.lock();
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		Sessions.erase(it);
	SessionsMutex.unlock();
}

GameServer* World::GetGameServer(uint16 Guid)
{
	GameServer* G = NULL;
	GameServersMutex.lock();
	GameServerMap::iterator it = GameServers.find(Guid);
	if(it != GameServers.end())
		G = it->second;
	GameServersMutex.unlock();
	return G;
}

void World::AddGameSession(GameSession* s)
{
	GameSessionsMutex.lock();
	GameSessions[s->GetServer()->GetID()] = s;
	GameSessionsMutex.unlock();
}

GameSession* World::GetGameSession(uint16 guid)
{
	GameSession* s = NULL;
	GameSessionsMutex.lock();
	GameSessionMap::iterator it = GameSessions.find(guid);
	if(it != GameSessions.end())
		s = it->second;
	GameSessionsMutex.unlock();
	return s;
}

void World::DeleteGameSession(uint16 guid)
{
	GameSessionsMutex.lock();
	GameSessionMap::iterator it = GameSessions.find(guid);
	if(it != GameSessions.end())
		GameSessions.erase(it);
	GameSessionsMutex.unlock();
}
