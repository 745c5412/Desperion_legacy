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

#ifndef __DATABASE__
#define __DATABASE__

template<class T>
struct Connection 
{
	T* conn;
	boost::mutex lock;

	Connection()
	{
	}

	Connection(const Connection& c)
	{
	}

	Connection<T>& operator =(const Connection& c)
	{ return *this; }
};

enum DatabaseType
{
	MYSQL_DATABASE,
	POSTGRE_SQL_DATABASE,
};

typedef Connection<PGconn> PConnection;
typedef Connection<MYSQL> MConnection;
typedef std::vector<boost::shared_array<const char> > QueryVector;

// mécanisme de type erasure pour une meilleure flexibilité
class TypeErasureDatabase
{
public:
	virtual bool Init(const std::string&, uint16, const std::string&, const std::string&, const std::string&) = 0;
	virtual std::string EscapeString(std::string) = 0;
	virtual ResultPtr Query(const char*, ...) = 0;
	virtual bool Execute(const char*, ...) = 0;
	virtual void AsyncExecute(const char*, ...) = 0;
	virtual void AsyncExecute(const QueryVector&) = 0;
	virtual void AsyncQuery(boost::function<void(ResultPtr)>, const char*, ...) = 0;
};

template<class T>
class Database : public TypeErasureDatabase
{
protected:
	std::vector<Connection<T> > m_connections;
	std::string m_hostName, m_userName, m_password, m_databaseName;
	uint16 m_port;
	boost::asio::io_service& m_service;

	virtual bool _Execute(Connection<T>*, const char*) = 0;
	virtual ResultPtr _Query(Connection<T>*, const char*) = 0;
	virtual bool Connect(Connection<T>*) = 0;
	
	Connection<T>* GetFreeConnection()
	{
		uint32 i = 0;
		size_t size = m_connections.size();
		for(;;)
		{
			Connection<T>* con = &m_connections[((i++) % size)];
			if(con->lock.try_lock())
				return con;
			if(!(i % 20))
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		return NULL;
	}

	void _AsyncExecute(boost::shared_array<const char> sql)
	{
		Connection<T>* con = GetFreeConnection();
		_Execute(con, sql.get());
		con->lock.unlock();
	}

	void _AsyncQuery(boost::function<void(ResultPtr)> callback, boost::shared_array<const char> sql)
	{
		Connection<T>* con = GetFreeConnection();
		ResultPtr qResult = _Query(con, sql.get());
		con->lock.unlock();
		callback(qResult);
	}

public:
	Database(boost::asio::io_service& ios, size_t size) : m_service(ios),
		m_connections(size)
	{
		for(size_t a = 0; a < size; ++a)
			m_connections[a].conn = NULL;
	}

	bool Init(const std::string& host, uint16 port, const std::string& user, const std::string& pass, const std::string& name)
	{
		m_hostName = host;
		m_port = port;
		m_userName = user;
		m_password = pass;
		m_databaseName = name;
		
		for(size_t a = 0; a < m_connections.size(); ++a)
			if(!Connect(&m_connections[a]))
				return false;
		return true;
	}

	ResultPtr Query(const char* queryString, ...)
	{	
		char sql[32768];
		va_list vlist;
		va_start(vlist, queryString);
		vsnprintf(sql, 32768, queryString, vlist);
		va_end(vlist);
		Connection<T>* con = GetFreeConnection();
		ResultPtr qResult = _Query(con, sql);
		con->lock.unlock();
		return qResult;
	}

	bool Execute(const char* queryString, ...)
	{
		char sql[32768];
		va_list vlist;
		va_start(vlist, queryString);
		vsnprintf(sql, 32768, queryString, vlist);
		va_end(vlist);
		Connection<T>* con = GetFreeConnection();
		bool result = _Execute(con, sql);
		con->lock.unlock();
		return result;
	}

	void AsyncExecute(const char* queryString, ...)
	{
		char sql[32768];
		va_list vlist;
		va_start(vlist, queryString);
		vsnprintf(sql, 32768, queryString, vlist);
		va_end(vlist);
		size_t size = strlen(sql);
		char* buf = new char[size + 1];
		memcpy(buf, sql, size + 1);
		m_service.post(boost::bind(&Database::_AsyncExecute, this, boost::shared_array<const char>(buf)));
	}

	void AsyncExecute(const QueryVector& queries)
	{
		if(queries.empty())
			return;
		std::string query = "";
		for(size_t a = 0; a < queries.size(); ++a)
			query += queries[a].get();
		size_t size = query.size();
		char* buf = new char[size + 1];
		memcpy(buf, &query[0], size);
		buf[size] = 0x0;
		m_service.post(boost::bind(&Database::_AsyncExecute, this, boost::shared_array<const char>(buf)));
	}

	void AsyncQuery(boost::function<void(ResultPtr)> callback, const char* queryString, ...)
	{
		char sql[32768];
		va_list vlist;
		va_start(vlist, queryString);
		vsnprintf(sql, 32768, queryString, vlist);
		va_end(vlist);
		size_t size = strlen(sql);
		char* buf = new char[size + 1];
		memcpy(buf, sql, size + 1);
		m_service.post(boost::bind(&Database::_AsyncQuery, this, callback, boost::shared_array<const char>(buf)));
	}
};

#endif