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
	typedef std::tr1::unordered_map<uint16, GameServer*> GameServerMap;
	typedef std::tr1::unordered_map<int, Session*> SessionMap;
	typedef std::tr1::unordered_map<int, GameSession*> GameSessionMap;

	World();
	~World();

	void Init();
	void LoadGameServers();

	void AddSession(Session*);
	void DeleteSession(int);
	Session* GetSession(int);

	void AddGameSession(GameSession*);
	void DeleteGameSession(uint16);
	GameSession* GetGameSession(uint16);

	GameServer* GetGameServer(uint16);
	void RefreshGameServer(GameServer*);


	uint16 GetPlayers() const
	{ return Sessions.size(); }

	uint16 GetMaxPlayers() const
	{ return m_maxPlayers; }

	const GameServerMap& GetGameServers() const
	{ return GameServers; }
private:
	SessionMap Sessions;
	GameSessionMap GameSessions;
	GameServerMap GameServers;

	time_t m_startTime;
	uint16 m_maxPlayers;

	Mutex SessionsMutex;
	Mutex GameSessionsMutex;
	Mutex GameServersMutex;
};

#endif