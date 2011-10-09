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