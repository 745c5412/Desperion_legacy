#include "StdAfx.h"

template <> World * Singleton<World>::m_singleton = NULL;
AtomicLog World::Logger("World", TNORMAL);

World::World()
{
	m_maxPlayers = 0;
}

void World::Update()
{
	SessionsMutex.lock();
	std::list<SessionSet::iterator> toErase;
	for(SessionSet::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		if((*it)->IsDead())
		{
			delete *it;
			toErase.push_back(it);
		}
	}
	for(std::list<SessionSet::iterator>::iterator it = toErase.begin(); it != toErase.end(); ++it)
		Sessions.erase(*it);
	SessionsMutex.unlock();

	GameSessionsMutex.lock();
	std::list<GameSessionSet::iterator> toErase2;
	for(GameSessionSet::iterator it = GameSessions.begin(); it != GameSessions.end(); ++it)
	{
		if((*it)->IsDead())
		{
			delete *it;
			toErase2.push_back(it);
		}
	}
	for(std::list<GameSessionSet::iterator>::iterator it = toErase2.begin(); it != toErase2.end(); ++it)
		GameSessions.erase(*it);
	GameSessionsMutex.unlock();
}

void World::RefreshGameServer(GameServer* G)
{
	SessionsMutex.lock();
	for(SessionSet::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		uint32 guid = (*it)->GetData(FLAG_GUID).intValue;
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

		(*it)->Send(ServerStatusUpdateMessage((*it)->GetServerStatusMessage(G, count)));
	}
	SessionsMutex.unlock();
}

World::~World()
{
	for(SessionSet::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
		delete *it;
	Sessions.clear();
	for(GameSessionSet::iterator it = GameSessions.begin(); it != GameSessions.end(); ++it)
		delete *it;
	GameSessions.clear();

	for(GameServerStorageMap::iterator it = GameServers.begin(); it != GameServers.end(); ++it)
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

void World::AddSession(Session* r)
{
	SessionsMutex.lock();
	Sessions.insert(r);
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
	SessionsMutex.unlock();
}

void World::AddGameSession(GameSession* r)
{
	GameSessionsMutex.lock();
	GameSessions.insert(r);
	GameSessionsMutex.unlock();
}

GameServer* World::GetGameServer(uint16 Guid)
{
	GameServer* G = NULL;
	GameServersMutex.lock();
	GameServerStorageMap::iterator it = GameServers.find(Guid);
	if(it != GameServers.end())
		G = it->second;
	GameServersMutex.unlock();
	return G;
}

GameSession* World::GetGameSession(uint16 id)
{
	GameSession* R = NULL;
	GameSessionsMutex.lock();
	for(GameSessionSet::iterator it = GameSessions.begin(); it != GameSessions.end(); ++it)
	{
		GameServer* G = (*it)->GetServer();
		if(G != NULL && id == G->GetID())
		{
			R = *it;
			break;
		}
	}
	GameSessionsMutex.unlock();
	return R;
}

void World::DeleteGameSession(GameSession* s)
{
	GameSessionsMutex.lock();
	GameSessionSet::iterator it = GameSessions.find(s);
	if(it != GameSessions.end())
		GameSessions.erase(it);
	GameSessionsMutex.unlock();
}

Session* World::GetSession(uint32 guid)
{
	Session* R = NULL;
	if(guid == 0)
		return R;
	SessionsMutex.lock();
	for(SessionSet::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		if(guid == (*it)->GetData(FLAG_GUID).intValue)
		{
			R = *it;
			break;
		}
	}
	SessionsMutex.unlock();
	return R;
}

void World::DeleteSession(Session* s)
{
	SessionsMutex.lock();
	SessionSet::iterator it = Sessions.find(s);
	if(it != Sessions.end())
		Sessions.erase(it);
	SessionsMutex.unlock();
}
