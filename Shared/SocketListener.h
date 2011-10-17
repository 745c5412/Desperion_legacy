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

#ifndef __SOCKET_LISTENER__
#define __SOCKET_LISTENER__

typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::ip::tcp::endpoint Endpoint;
typedef boost::asio::ip::tcp::socket Socket;
typedef boost::asio::io_service Service;

template<class T>
class SocketListener
{
public:
	typedef boost::shared_ptr<T> SessionPtr;
private:
	Acceptor* m_acceptor;
	Socket* m_socket;
	Service& m_service;
public:
	SocketListener(Service& service) : m_service(service)
	{
		m_acceptor = NULL;
		m_socket = NULL;
	}

	void Init(uint16 port)
	{
		m_acceptor = new boost::asio::ip::tcp::acceptor(m_service, 
			boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port));
		m_socket = new Socket(m_service);
	}

	~SocketListener()
	{
		if(m_acceptor->is_open())
			m_acceptor->close();
		delete m_acceptor;
		delete m_socket;
	}

	void HandleAcceptSocket(const boost::system::error_code& error)
	{
		if(error)
			return;
		SessionPtr session(new T);
		session->Init(m_socket);
		m_socket = new Socket(m_service);
		session->Start();
		Run();
	}

	void Run()
	{
		m_acceptor->async_accept(*m_socket, boost::bind(&SocketListener::HandleAcceptSocket, this, boost::asio::placeholders::error));
	}

	bool IsOpen()
	{
		return m_acceptor->is_open();
	}
};

#endif