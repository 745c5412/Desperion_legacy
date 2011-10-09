#ifndef __SOCKET_LISTENER__
#define __SOCKET_LISTENER__

template<class T>
class SocketListener
{
public:
	typedef boost::asio::ip::tcp::acceptor Acceptor;
	typedef boost::asio::ip::tcp::endpoint Endpoint;
	typedef boost::asio::ip::tcp::socket Socket;
	typedef boost::asio::io_service Service;
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
		{
			m_acceptor->close();
			m_acceptor->cancel();
		}
		delete m_acceptor;
		delete m_socket;
	}

	void OnAccept(const boost::system::error_code& error)
	{
		if(error)
			return;
		T* session = new T;
		session->Init(m_socket);
		m_socket = new Socket(m_service);
		session->Start();
		Run();
	}

	void Run()
	{
		m_acceptor->async_accept(*m_socket, boost::bind(&SocketListener::OnAccept, this, boost::asio::placeholders::error));
	}

	bool IsOpen()
	{
		return m_acceptor->is_open();
	}
};

#endif