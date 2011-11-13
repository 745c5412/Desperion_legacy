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

template<> GameClient * Singleton<GameClient>::m_singleton = NULL;
template<> GameClient::HandlerStorageMap AbstractSession<ComPacketHandler>::m_handlers;

GameClient::~GameClient()
{
}

void GameClient::Launch()
{
	if(m_timer == NULL)
		m_timer = new boost::asio::deadline_timer(m_socket->io_service());
	else
		m_timer->cancel();
	m_socket->close();
	boost::asio::ip::tcp::endpoint host(boost::asio::ip::address::from_string("127.0.0.1"),
		Desperion::Config::Instance().GetUInt(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
	m_socket->async_connect(host, boost::bind(&GameClient::HandleConnect, this, boost::asio::placeholders::error));
}

void GameClient::HandleConnect(const boost::system::error_code& error)
{
	if(error)
	{
		Log::Instance().outDebug("Problems with game client connection, waiting 5 seconds...");
		m_timer->expires_from_now(boost::posix_time::seconds(5));
		m_timer->async_wait(boost::bind(&GameClient::Launch, this));
	}
	else
		Start();
}

void GameClient::Start()
{
	ByteBuffer dest, src;

	src<<uint16(Desperion::Config::Instance().GetUInt(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT));
	src<<Desperion::Config::Instance().GetString(LOCAL_SERVER_AUTH_KEY_STRING, LOCAL_SERVER_AUTH_KEY_DEFAULT);
	Packet::Pack(CMSG_CONNECT, dest, src);
	_Send(dest);
	
	dest.Clear();
	src.Clear();

	src<<m_state;
	Packet::Pack(CMSG_STATE, dest, src);
	_Send(dest);

	Run();
}