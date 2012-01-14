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

#ifndef __ABSTRACT_SESSION__
#define __ABSTRACT_SESSION__

template<class HandlerType>
class AbstractSession : public boost::enable_shared_from_this<AbstractSession<HandlerType> >
{
protected:
	typedef std::tr1::unordered_map<uint32, HandlerType> HandlerStorageMap;
	static HandlerStorageMap m_handlers;
	time_t m_startTime;
	boost::asio::ip::tcp::socket* m_socket;

	
	void _Send(ByteBuffer& buffer)
	{
		const uint8* contents = buffer.Contents();
		try{
		boost::asio::write(*m_socket, boost::asio::buffer(contents, buffer.Size()));
		}catch(...){ }
	}
private:
	uint8 m_header[2];
	uint16 m_opcode;
	std::vector<uint8> m_length;
	std::vector<uint8> m_buffer;
	std::queue<boost::shared_ptr<ByteBuffer> > m_packets;
	bool m_isSharedPtr;
public:
	virtual void Start() = 0;
	virtual bool IsAllowed(uint8 flag) = 0;
	virtual void HandleData(HandlerType* hdl, ByteBuffer& packet) = 0;

	AbstractSession(bool isSharedPtr = true) : m_startTime(time(NULL)),
		m_isSharedPtr(isSharedPtr), m_opcode(0)
	{
	}

	virtual ~AbstractSession()
	{
		if(m_socket->is_open())
			m_socket->close();
		delete m_socket;
	}

	void Send(DofusMessage& message)
	{
		uint16 opcode = message.GetOpcode();
		Log::Instance().outDebug("Sent: <%u> | <%s>", opcode, typeid(message).name());
		ByteBuffer dest, src;
		message.Serialize(src);
		Packet::Pack(opcode, dest, src);
		_Send(dest);
	}

	void Init(boost::asio::ip::tcp::socket* socket)
	{ m_socket = socket; }

	virtual void HandleError()
	{ }

	void HandleReadLength(const boost::system::error_code& error)
	{
		if(error)
		{
			HandleError();
			return;
		}
		uint32 length = 0;
		for(uint8 a = 0; a < m_length.size(); ++a)
			length = (length << 8) + m_length[a];
		m_buffer.resize(length);
		m_length.clear();
		if(m_isSharedPtr)
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_buffer), boost::bind(&AbstractSession::HandleReadContent,
				shared_from_this(), boost::asio::placeholders::error));
		}
		else
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_buffer), boost::bind(&AbstractSession::HandleReadContent,
				this, boost::asio::placeholders::error));
		}
	}

	void HandleReadHeader(const boost::system::error_code& error)
	{
		if(error)
		{
			HandleError();
			return;
		}
		uint16 header = *((uint16*)&m_header[0]);
		if(ByteBuffer::ENDIANNESS == LITTLE_ENDIAN)
			SwapBytes((uint8*)&header, sizeof(header));
		m_opcode = header >> 2;
		uint8 typeLen = header & 3;
		m_length.resize(typeLen);
		if(m_isSharedPtr)
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_length), boost::bind(&AbstractSession::HandleReadLength,
				shared_from_this(), boost::asio::placeholders::error));
		}
		else
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_length), boost::bind(&AbstractSession::HandleReadLength,
				this, boost::asio::placeholders::error));
		}
	}

	void AsyncHandleData(HandlerType hdl)
	{
		boost::shared_ptr<ByteBuffer> buf = m_packets.front();
		m_packets.pop();
		try{
		HandleData(&hdl, *buf);
		}catch(const boost::exception&){
		}catch(const std::exception& except)
		{ Log::Instance().outError(except.what()); }
	}

	void HandleReadContent(const boost::system::error_code& error)
	{
		if(error)
		{
			HandleError();
			return;
		}
		Log::Instance().outDebug("Received: <%u>", m_opcode);
		HandlerStorageMap::iterator it = AbstractSession::m_handlers.find(m_opcode);
		if(it != AbstractSession::m_handlers.end())
		{
			HandlerType hdl = it->second;
			if(IsAllowed(hdl.Flag))
			{
				ByteBuffer* received = new ByteBuffer;
				size_t size = m_buffer.size();
				if(size > 0)
					received->AppendBytes(&m_buffer[0], size);
				m_packets.push(boost::shared_ptr<ByteBuffer>(received));
				if(m_isSharedPtr)
					ThreadPool::Instance().Schedule(boost::bind(&AbstractSession::AsyncHandleData, shared_from_this(), hdl));
				else
					ThreadPool::Instance().Schedule(boost::bind(&AbstractSession::AsyncHandleData, this, hdl));
			}
		}
		m_opcode = 0;
		m_buffer.clear();
		Run();
	}

	void Run()
	{
		if(m_isSharedPtr)
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_header), boost::bind(&AbstractSession::HandleReadHeader,
				shared_from_this(), boost::asio::placeholders::error));
		}
		else
		{
			boost::asio::async_read(*m_socket, boost::asio::buffer(m_header), boost::bind(&AbstractSession::HandleReadHeader,
				this, boost::asio::placeholders::error));
		}
	}

	boost::asio::ip::tcp::socket* GetSocket()
	{ return m_socket; }

	time_t GetStartTime() const
	{ return m_startTime; }
};

#endif