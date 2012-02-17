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

MySQLDatabase::~MySQLDatabase()
{
	for(uint8 a = 0; a < m_connections.size(); ++a)
	{
		if(!m_connections[a].conn)
			continue;
		mysql_close(m_connections[a].conn);
	}
}

bool MySQLDatabase::Connect(MConnection* conn)
{
	MYSQL* temp = NULL, * temp2 = NULL;
	my_bool my_true = true;
	temp = mysql_init(NULL);
	if(mysql_options(temp, MYSQL_SET_CHARSET_NAME, "utf8"))
		Log::Instance().OutError("MySQLDatabase: Could not set utf8 character set.");
	else if(mysql_options(temp, MYSQL_OPT_RECONNECT, &my_true))
		Log::Instance().OutError("MySQLDatabase: MYSQL_OPT_RECONNECT could not be set, connection drops may occur but will be counteracted.");
	temp2 = mysql_real_connect(temp, m_hostName.c_str(), m_userName.c_str(), m_password.c_str(), m_databaseName.c_str(), m_port, NULL, 0);
	if(temp2 == NULL)
	{
		Log::Instance().OutError("MySQLDatabase: Connection failed due to: `%s`", mysql_error(temp));
		mysql_close(temp);
		return false;
	}
	if(conn->conn != NULL)
		mysql_close(conn->conn);
	conn->conn = temp;
	if(!SendQuery(conn, "SET SESSION sql_mode='ANSI_QUOTES';", false)) // compatibilité avec postgreSQL
	{
		Log::Instance().OutError("[FATAL] MySQLDatabase: sql_mode='ANSI_QUOTES' could not be set, Desperion can't continue.");
		return false;
	}
	return true;
}

bool MySQLDatabase::HandleError(MConnection* con, uint32 errorNumber)
{
	switch(errorNumber)
	{
	case 2006: // Mysql server has gone away
	case 2008: // Client ran out of memory
	case 2013: // Lost connection to sql server during query
	case 2055: // Lost connection to sql server - system error
			return Connect(con);
	}
	return false;
}

bool MySQLDatabase::SendQuery(MConnection* con, const char* sql, bool self)
{
	int result = mysql_query(con->conn, sql);
	if(result > 0)
	{
		if(!self && HandleError(con, mysql_errno(con->conn)))
			result = SendQuery(con, sql, true);
		else
			Log::Instance().OutError("MySQLDatabase: Sql query failed due to [%s], Query: [%s]\n", mysql_error(con->conn), sql);
	}
	return (result == 0 ? true : false);
}

bool MySQLDatabase::_Execute(MConnection* con, const char* sql)
{
	return SendQuery(con, sql, false);
}

ResultPtr MySQLDatabase::_Query(MConnection* con, const char* sql)
{
	ResultPtr QR;
	if(SendQuery(con, sql, false))
	{
		MYSQL_RES * pRes = mysql_store_result(con->conn);
		uint32 uRows = (uint32) mysql_affected_rows(con->conn);
		if(uRows != 0)
		{
			uint32 uFields = (uint32) mysql_field_count(con->conn);
			QR.reset(new QueryResult(pRes, uFields, uRows));
		}
	}
	return QR;
}

std::string MySQLDatabase::EscapeString(std::string str)
{
	size_t size = str.length();
	char* buffer = new char[size * 2 + 1];
	MConnection* con = GetFreeConnection();
	const char* result = "";
	if(mysql_real_escape_string(con->conn, buffer, str.c_str(), size) == 0)
		result = buffer;
	con->lock.unlock();
	std::string ret(result);
	delete[] buffer;
	return ret;
}