#include "StdAfx.h"

Database::Database(uint8 number)
{
	m_connections_number = number;
	m_connections = new Connection[m_connections_number];
	for(uint8 a = 0; a < m_connections_number; ++a)
		m_connections[a].conn = NULL;
}

Database::~Database()
{
	for(uint8 a = 0; a < m_connections_number; ++a)
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
	m_host_name = host;
	m_port = port;
	m_user_name = user;
	m_password = pass;
	m_database_name = name;

	MYSQL* temp, * temp2;
	my_bool my_true = true;

	for(uint8 a = 0; a < m_connections_number; ++a)
	{
		temp = mysql_init( NULL );
		if(mysql_options(temp, MYSQL_SET_CHARSET_NAME, "utf8"))
			Log::Instance().outError("MySQLDatabase: Could not set utf8 character set.");

		if (mysql_options(temp, MYSQL_OPT_RECONNECT, &my_true))
			Log::Instance().outError("MySQLDatabase: MYSQL_OPT_RECONNECT could not be set, connection drops may occur but will be counteracted.");

		temp2 = mysql_real_connect( temp, m_host_name.c_str(), m_user_name.c_str(), m_password.c_str(), m_database_name.c_str(), port, NULL, 0 );
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
	temp2 = mysql_real_connect( temp, m_host_name.c_str(), m_user_name.c_str(), m_password.c_str(), m_database_name.c_str(), m_port, NULL , 0 );
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

bool Database::HandleError(Connection * con, uint32 ErrorNumber)
{
	// Handle errors that should cause a reconnect to the Database.
	switch(ErrorNumber)
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
		Connection * con = &m_connections[ ((i++) % m_connections_number) ];
		if(con->mymutex.try_lock())
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
	con->mymutex.unlock();

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
	con->mymutex.unlock();

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
	con->mymutex.unlock();

	return qResult;
}

QueryResult::QueryResult(MYSQL_RES *res, uint32 fields, uint32 rows) : mResult(res), mFieldCount(fields), mRowCount(rows)
{
	mCurrentRow = new Field[fields];
}

QueryResult::~QueryResult()
{
	mysql_free_result(mResult);
	delete [] mCurrentRow;
}

bool QueryResult::NextRow()
{
	MYSQL_ROW row = mysql_fetch_row(mResult);
	if(row == NULL)
		return false;

	for(uint32 i = 0; i < mFieldCount; ++i)
		mCurrentRow[i].SetValue(row[i]);

	return true;
}