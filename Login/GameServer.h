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

#ifndef __GAME_SERVER__
#define __GAME_SERVER__

class GameSession;

enum ServerStatus
{
	STATUS_UNKNOWN = 0,
	OFFLINE = 1,
	STARTING = 2,
	ONLINE = 3,
	NOJOIN = 4,
	SAVING = 5,
	STOPING = 6,
	FULL = 7,
};

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