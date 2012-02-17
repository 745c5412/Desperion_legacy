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

class GameSession : public AbstractSession<GamePacketHandler>
{
private:
	GameServer* m_server;

	void HandleStateMessage(ByteBuffer&);
	void HandlePlayersMessage(ByteBuffer&);
	void HandleConnectMessage(ByteBuffer&);
public:
	void SendDisconnectPlayerMessage(int);
	static void InitHandlersTable();

	void Start() 
	{ Run(); }

	void HandleData(GamePacketHandler* hdl, ByteBuffer& packet)
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

	GameSession(boost::asio::io_service& ios) : AbstractSession<GamePacketHandler>(ios),
		m_server(NULL)
	{
	}

	~GameSession();

	GameServer* GetServer()
	{ return m_server; }
};

#endif