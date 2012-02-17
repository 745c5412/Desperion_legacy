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

#ifndef __SOCKET_LISTENER__
#define __SOCKET_LISTENER__

template<class T>
class SocketListener
{
public:
	typedef boost::shared_ptr<T> SessionPtr;
private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::io_service& m_service;
	SessionPtr m_session;
public:
	SocketListener(boost::asio::io_service& ios, uint16 port) : m_service(ios),
		m_acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port)),
		m_session(new T(ios))
	{
		Run();
	}

	~SocketListener()
	{
		if(m_acceptor.is_open())
			m_acceptor.close();
	}

	bool HandleError(const boost::system::error_code& error)
	{
		if(!error)
			return false;
		Log::Instance().OutError("SocketListener: [%u] %s", error.value(), error.message().c_str());
		return true;
	}

	void HandleAcceptSocket(const boost::system::error_code& error)
	{
		if(!HandleError(error))
		{
			m_session->GetSocket().set_option(boost::asio::ip::tcp::no_delay(true));
			m_session->Start();
			m_session.reset(new T(m_service));
		}
		Run();
	}

	void Run()
	{
		m_acceptor.async_accept(m_session->GetSocket(),
			boost::bind(&SocketListener::HandleAcceptSocket, this, boost::asio::placeholders::error));
	}
};

#endif