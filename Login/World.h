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

#ifndef __WORLD__
#define __WORLD__

class GameServer;
class Session;
class GameSession;

typedef boost::mutex Mutex;

class World : public Singleton<World>
{
	friend class Singleton<World>;
public:
	/* arrays typedefs */
	typedef std::tr1::unordered_map<uint16, GameServer*> GameServerStorageMap;
	typedef std::set<Session*> SessionSet;
	typedef std::set<GameSession*> GameSessionSet;

	World();
	~World();

	void Update();
	void Init();
	void LoadGameServers();

	void AddSession(Session*);
	void DeleteSession(Session*);
	Session* GetSession(uint32);
	void AddGameSession(GameSession*);
	void DeleteGameSession(GameSession*);
	GameSession* GetGameSession(uint16);

	GameServer* GetGameServer(uint16);
	void RefreshGameServer(GameServer*);


	uint16 GetPlayers() const
	{ return Sessions.size(); }

	uint16 GetMaxPlayers() const
	{ return m_maxPlayers; }

	const GameServerStorageMap& GetGameServers() const
	{ return GameServers; }
private:
	static AtomicLog Logger;

	SessionSet Sessions;
	GameSessionSet GameSessions;
	GameServerStorageMap GameServers;

	time_t m_startTime;
	uint16 m_maxPlayers;

	Mutex SessionsMutex;
	Mutex GameSessionsMutex;
	Mutex GameServersMutex;
};

#endif