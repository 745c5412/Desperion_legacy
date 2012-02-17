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

#ifndef __GAME_CLIENT__
#define __GAME_CLIENT__

class GameClient;
typedef boost::asio::io_service Service;

struct ComPacketHandler
{
	uint8 Flag;
	void (GameClient::*Handler)(ByteBuffer&);
};

class GameClient : public AbstractSession<ComPacketHandler>, public Singleton<GameClient>
{
private:
	uint8 m_state;
	boost::shared_ptr<boost::asio::deadline_timer> m_timer;

	void HandleConnect(const boost::system::error_code&);
	void HandleDisconnectPlayerMessage(ByteBuffer&);
public:

	uint8 GetState() const
	{ return m_state; }

	void SendPlayers()
	{
		ByteBuffer dest, src;
		src<<World::Instance().GetPlayers();
		Packet::Pack(CMSG_PLAYERS, dest, src);
		_Send(dest);
	}

	bool IsAllowed(uint8 flag)
	{ return true; }

	GameClient(boost::asio::io_service& ios) : AbstractSession<ComPacketHandler>(ios, false),
		m_state(3)
	{
		m_handlers[SMSG_DISCONNECT_PLAYER].Handler = &GameClient::HandleDisconnectPlayerMessage;
	}

	void GameClientError()
	{ Launch(); }

	void Launch();
	void Start();

	void HandleData(ComPacketHandler* hdl, ByteBuffer& packet)
	{ (this->*hdl->Handler)(packet); }
};

#endif