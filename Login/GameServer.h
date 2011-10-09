#ifndef __GAME_SERVER__
#define __GAME_SERVER__

class GameSession;

class GameServer
{
private:
	uint16 m_id;
	std::string m_ip;
	uint16 m_port;
	uint8 m_state;
	std::string m_key;
	uint16 m_pLimit;
	uint16 m_players;
	uint8 m_minLevel;
public:
	void Init(uint16, std::string, uint16, uint8, std::string, uint16, uint8);
	GameServer();

	uint8 GetMinLevel() const
	{ return m_minLevel; }

	std::string GetKey() const
	{ return m_key; }

	uint16 GetID() const
	{ return m_id; }

	std::string GetIP() const
	{ return m_ip; }

	uint16 GetLimit() const
	{ return m_pLimit; }

	uint16 GetPort() const
	{ return m_port; }

	uint8 GetState(uint8, bool) const;

	void SetState(uint8 st)
	{ m_state = st; }

	uint16 GetPlayers() const
	{ return m_players; }

	void SetPlayers(uint16 pl)
	{ m_players = pl; }
};

#endif