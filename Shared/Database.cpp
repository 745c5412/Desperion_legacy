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

#include "StdAfx.h"

Database::Database(uint8 number)
{
	m_connectionsNumber = number;
	m_connections = new Connection[m_connectionsNumber];
	for(uint8 a = 0; a < m_connectionsNumber; ++a)
		m_connections[a].conn = NULL;
}

Database::~Database()
{
	for(uint8 a = 0; a < m_connectionsNumber; ++a)
	{
		if(!m_connections[a].conn)
			continue;
		mysql_close(m_connections[a].conn);
		m_connections[a].conn = NULL;
	}
	delete[] m_connections;
}

bool Database::Init(std::string host, uint16 port, std::string user, std::string pass, std::string name)
{
	m_hostName = host;
	m_port = port;
	m_userName = user;
	m_password = pass;
	m_databaseName = name;

	MYSQL* temp, * temp2;
	my_bool my_true = true;

	for(uint8 a = 0; a < m_connectionsNumber; ++a)
	{
		temp = mysql_init( NULL );
		if(mysql_options(temp, MYSQL_SET_CHARSET_NAME, "utf8"))
			Log::Instance().outError("MySQLDatabase: Could not set utf8 character set.");

		if (mysql_options(temp, MYSQL_OPT_RECONNECT, &my_true))
			Log::Instance().outError("MySQLDatabase: MYSQL_OPT_RECONNECT could not be set, connection drops may occur but will be counteracted.");

		temp2 = mysql_real_connect( temp, m_hostName.c_str(), m_userName.c_str(), m_password.c_str(), m_databaseName.c_str(), port, NULL, 0 );
		if( temp2 == NULL )
		{
			Log::Instance().outError("MySQLDatabase: Connection failed due to: `%s`", mysql_error( temp ) );
			return false;
		}
		m_connections[a].conn = temp2;
	}
	return true;
}

bool Database::Reconnect(Connection * conn)
{
	MYSQL * temp, *temp2;

	temp = mysql_init( NULL );
	temp2 = mysql_real_connect( temp, m_hostName.c_str(), m_userName.c_str(), m_password.c_str(), m_databaseName.c_str(), m_port, NULL , 0 );
	if( temp2 == NULL )
	{
		Log::Instance().outError("Database: Could not reconnect to database because of `%s`", mysql_error( temp ) );
		mysql_close( temp );
		return false;
	}

	if( conn->conn != NULL )
		mysql_close( conn->conn );

	conn->conn = temp;
	return true;
}

bool Database::HandleError(Connection * con, uint32 errorNumber)
{
	// Handle errors that should cause a reconnect to the Database.
	switch(errorNumber)
	{
	case 2006:  // Mysql server has gone away
	case 2008:  // Client ran out of memory
	case 2013:  // Lost connection to sql server during query
	case 2055:  // Lost connection to sql server - system error
		{
			// Let's instruct a reconnect to the db when we encounter these errors.
			return Reconnect( con );
		}break;
	}

	return false;
}

bool Database::SendQuery(Connection* con, const char* Sql, bool Self)
{
	int result = mysql_query(con->conn, Sql);
	if(result > 0)
	{
		if( Self == false && HandleError(con, mysql_errno( con->conn ) ) )
			result = SendQuery(con, Sql, true);
		else
			Log::Instance().outError("Database: Sql query failed due to [%s], Query: [%s]\n", mysql_error( con->conn ), Sql);
	}

	return (result == 0 ? true : false);
}

Connection* Database::GetFreeConnection()
{
	uint32 i = 0;
	for(;;)
	{
		Connection * con = &m_connections[ ((i++) % m_connectionsNumber) ];
		if(con->lock.try_lock())
			return con;

		if( !(i % 20) )
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}

	return NULL;
}

/* 
	je suis obligé d'écrire une fonction spéciale car boost::bind
	ne gère pas les listes d'arguments '...'
*/
void Database::AsyncExecute(const char* QueryString, ...)
{
	char query[32768];

	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(query, 32768, QueryString, vlist);
	va_end(vlist);

	boost::thread(boost::bind(&Database::_AsyncExecute, this, query));
}

bool Database::_AsyncExecute(const char* query)
{
	Connection* con = GetFreeConnection();
	bool result = SendQuery(con, query, false);
	con->lock.unlock();

	return result;
}

bool Database::Execute(const char* QueryString, ...)
{
	char query[32768];

	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(query, 32768, QueryString, vlist);
	va_end(vlist);

	Connection* con = GetFreeConnection();
	bool result = SendQuery(con, query, false);
	con->lock.unlock();

	return result;
}

QueryResult* Database::StoreResult(Connection* con)
{
	QueryResult* qResult;

	MYSQL_RES * pRes = mysql_store_result( con->conn );
	uint32 uRows = (uint32)mysql_affected_rows( con->conn );
	uint32 uFields = (uint32)mysql_field_count( con->conn );

	if( uRows == 0 || uFields == 0 || pRes == 0 )
	{
		if( pRes != NULL )
			mysql_free_result( pRes );

		return NULL;
	}

	qResult = new QueryResult( pRes, uFields, uRows );
	qResult->NextRow();
	return qResult;
}

QueryResult * Database::Query(const char* QueryString, ...)
{	
	char sql[32768];
	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(sql, 32768, QueryString, vlist);
	va_end(vlist);

	// Send the query
	QueryResult * qResult = NULL;
	Connection * con = GetFreeConnection();

	if(SendQuery(con, sql, false))
		qResult = StoreResult(con);
	con->lock.unlock();

	return qResult;
}

std::string Database::EscapeString(std::string str)
{
	char a2[16384] = {0};

	Connection * con = GetFreeConnection();
	const char * ret;
	const char* escape = str.c_str();
	if(mysql_real_escape_string(con->conn, a2, escape, (unsigned long)str.length()) == 0)
		ret = escape;
	else
		ret = a2;

	con->lock.unlock();
	return std::string(ret);
}