#ifndef __GAME_SESSION__
#define __GAME_SESSION__

struct GamePacketHandler
{
	uint8 Flag;
	void (GameSession::*Handler)(ByteBuffer&);

	GamePacketHandler()
	{
		Flag = FLAG_CONNECTED;
	}
};

class GameSession : public BaseSession<GamePacketHandler>
{
private:
	GameServer* m_server;

	void HandleStateMessage(ByteBuffer&);
	void HandlePlayersMessage(ByteBuffer&);
	void HandleConnectMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	void Start() 
	{ Run(); }

	void OnData(GamePacketHandler* hdl, ByteBuffer& packet)
	{ (this->*hdl->Handler)(packet); }

	bool IsAllowed(uint8 flag)
	{
		switch(flag)
		{
		case FLAG_NOT_CONNECTED:
			return m_server == NULL;
		case FLAG_CONNECTED:
			return m_server != NULL;
		}
		return true;
	}

	GameSession()
	{ 
		m_server = NULL;
		World::Instance().AddGameSession(this);
	}

	~GameSession();

	GameServer* GetServer()
	{ return m_server; }
};

#endif