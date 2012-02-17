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

template <> World * Singleton<World>::m_singleton = NULL;

// A poster dans l'io_service du Master, car c'est une méthode assez lourde
void World::RefreshGameServer(GameServer* G)
{
	struct Count
	{
		uint8 count;
		Count()
		{ count = 0; }
	};
	std::tr1::unordered_map<int, Count> counts;
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"accountGuid\" FROM \"character_counts\" WHERE \"serverId\"=%u;", G->GetID());
	if(QR)
	{
		while(QR->NextRow())
		{
			Field* fields = QR->Fetch();
			++counts[fields[0].GetInt32()].count;
		}
	}

	boost::shared_lock<boost::shared_mutex> lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		it->second->Send(ServerStatusUpdateMessage(it->second->GetServerStatusMessage(G, 
			counts[it->second->GetData(FLAG_GUID).intValue].count)));
	}
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
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM \"game_servers\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field * fields = QR->Fetch();
		uint16 id = fields[0].GetUInt16();
		GameServer* g = new GameServer;
		g->Init(id, fields[1].GetString(), fields[2].GetUInt16(), fields[3].GetUInt8(), fields[5].GetString(), fields[4].GetUInt16(), fields[6].GetUInt8());
		GameServers[id] = g;
	}
	
	Log::Instance().OutNotice("World", "%u game servers loaded in %ums!", GameServers.size(), getMSTime() - time);
}

void World::Init()
{
	Log::Instance().OutNotice("World", "Loading world...");
	LoadGameServers();
	Session::InitHandlersTable();
	GameSession::InitHandlersTable();
	Log::Instance().OutNotice("World", "World loaded!\n\n");
}

void World::AddSession(Session* s)
{
	boost::unique_lock<boost::shared_mutex> lock(SessionsMutex);
	Sessions[s->GetData(FLAG_GUID).intValue] = s;
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
}

Session* World::GetSession(int guid)
{
	boost::shared_lock<boost::shared_mutex> lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		return it->second;
	return NULL;
}

void World::DeleteSession(int guid)
{
	boost::unique_lock<boost::shared_mutex> lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		Sessions.erase(it);
}

GameServer* World::GetGameServer(uint16 Guid)
{
	GameServerMap::iterator it = GameServers.find(Guid);
	if(it != GameServers.end())
		return it->second;
	return NULL;
}

void World::AddGameSession(GameSession* s)
{
	boost::unique_lock<boost::shared_mutex> lock(GameSessionsMutex);
	GameSessions[s->GetServer()->GetID()] = s;
}

GameSession* World::GetGameSession(uint16 guid)
{
	boost::shared_lock<boost::shared_mutex> lock(GameSessionsMutex);
	GameSessionMap::iterator it = GameSessions.find(guid);
	if(it != GameSessions.end())
		return it->second;
	return NULL;
}

void World::DeleteGameSession(uint16 guid)
{
	boost::unique_lock<boost::shared_mutex> lock(GameSessionsMutex);
	GameSessionMap::iterator it = GameSessions.find(guid);
	if(it != GameSessions.end())
		GameSessions.erase(it);
}
