#ifndef __DATABASE__
#define __DATABASE__


/*
	Based on AscentEmulator Database class
*/

struct Connection
{
	MYSQL* conn;
	boost::mutex lock;
	Connection() {}
	Connection(const Connection& that){}
};

class Database
{
private:
	Connection * m_connections;

	std::string m_hostName;
	std::string m_userName;
	std::string m_password;
	std::string m_databaseName;
	uint16 m_port;
	uint8 m_connectionsNumber;

	Connection* GetFreeConnection();
	bool SendQuery(Connection*, const char*, bool);
	QueryResult* StoreResult(Connection*);
	bool HandleError(Connection*, uint32);
	bool Reconnect(Connection*);
public:
	Database(uint8);
	~Database();
	std::string EscapeString(std::string);

	bool Init(std::string, uint16, std::string, std::string, std::string);

	QueryResult* Query(const char*, ...);
	bool Execute(const char*, ...);
	void AsyncExecute(const char*, ...);
	bool _AsyncExecute(const char*);
};

#endif