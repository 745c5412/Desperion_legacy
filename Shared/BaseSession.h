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

#ifndef __BASE_SESSION__
#define __BASE_SESSION__

typedef boost::asio::ip::tcp::socket Socket;

template<class HandlerType>
class BaseSession
{
protected:
	typedef std::tr1::unordered_map<uint32, HandlerType> HandlerStorageMap;
	static HandlerStorageMap m_handlers;
	time_t m_startTime;
	Socket* m_socket;
private:
	uint8 m_header[2];
	uint32 m_opcode;
	std::vector<uint8> m_length;
	std::vector<uint8> m_buffer;
	bool m_dead;

	void _Send(ByteBuffer& buffer)
	{
		buffer.HexLike();
		const uint8* contents = buffer.Contents();
		boost::asio::write(*m_socket, boost::asio::buffer(contents, buffer.Size()));
	}
public:
	virtual void Start() = 0;
	virtual bool IsAllowed(uint8 flag) = 0;
	virtual void OnData(HandlerType* hdl, ByteBuffer& packet) = 0;

	bool IsDead()
	{ return m_dead; }

	BaseSession()
	{ 
		m_startTime = time(NULL);
		m_dead = false;
	}

	virtual ~BaseSession()
	{
		if(m_socket->is_open())
			m_socket->close();
		delete m_socket;
	}

	void Send(const Packet& data)
	{
		_Send(data.Pack());
	}

	void Send(const DofusMessage& data)
	{
		Packet packet(data.GetOpcode());
		packet<<data.GetBuffer();
		Send(packet);
	}

	void Init(Socket* socket)
	{ m_socket = socket; }

	void CloseConnection()
	{
		m_dead = true;
		if(m_socket->is_open())
			m_socket->close();
	}

	void HandleReadLength(const boost::system::error_code& error)
	{
		if(error)
		{
			CloseConnection();
			return;
		}

		size_t toResize = 0;
		switch(m_length.size())
		{
		case 1:
			toResize = m_length[0];
			break;
		case 2:
			toResize = *((uint16*)&m_length[0]);
			if(ENDIANNESS)
				SWAP(toResize);
			break;
		case 3:
			toResize = (((m_length[0] & 0xff) << 0x10) + ((m_length[1] & 0xff) << 8)) + (m_length[2] & 0xff);
			break;
		}
		m_buffer.resize(toResize);
		m_length.clear();

		boost::asio::async_read(*m_socket, boost::asio::buffer(m_buffer), boost::bind(&BaseSession::HandleReadData, this, 
			boost::asio::placeholders::error));
	}

	void HandleReadHeader(const boost::system::error_code& error)
	{
		if(error)
		{
			CloseConnection();
			return;
		}

		uint16 header = *((uint16*)&m_header[0]);
		if(ENDIANNESS)
			SWAP(header);
		m_opcode = header >> 2;
		uint32 typeLen = header & 3;
		m_length.resize(typeLen);

		boost::asio::async_read(*m_socket, boost::asio::buffer(m_length), boost::bind(&BaseSession::HandleReadLength, this, 
			boost::asio::placeholders::error));
	}

	void HandleReadData(const boost::system::error_code& error)
	{
		if(error)
		{
			CloseConnection();
			return;
		}

		Log::Instance().outDebug("Received: packet ID %u", m_opcode);
		HandlerStorageMap::iterator it = BaseSession::m_handlers.find(m_opcode);

		if(it == BaseSession::m_handlers.end())
		{
			Send(Packet(SMSG_BASIC_NO_OPERATION));
			Run();
			return;
		}
			
		ByteBuffer received;
		received.AppendBytes(&m_buffer[0], m_buffer.size());

		HandlerType* hdl = &it->second;
		if(IsAllowed(hdl->Flag))
		{
			try
			{
				OnData(hdl, received);
			}catch(const ServerError& error)
			{
				Log::Instance().outError(error.what());
				m_dead = true;
				return;
			}catch(const std::exception& except)
			{
				Log::Instance().outError(except.what());
			}
		}
		
		m_opcode = 0;
		m_buffer.clear();
		Run();
	}

	void Run()
	{
		boost::asio::async_read(*m_socket, boost::asio::buffer(m_header), boost::bind(&BaseSession::HandleReadHeader, this, 
			boost::asio::placeholders::error));
	}

	Socket* GetSocket()
	{ return m_socket; }

	time_t GetStartTime() const
	{ return m_startTime; }
};

#endif