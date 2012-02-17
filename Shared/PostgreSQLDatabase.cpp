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

PostgreSQLDatabase::~PostgreSQLDatabase()
{
	for(uint8 a = 0; a < m_connections.size(); ++a)
	{
		if(!m_connections[a].conn)
			continue;
		PQfinish(m_connections[a].conn);
	}
}

bool PostgreSQLDatabase::Connect(PConnection* conn)
{
	PGconn* temp = PQsetdbLogin(m_hostName.c_str(), Desperion::ToString(m_port).c_str(), NULL, NULL,
		m_databaseName.c_str(), m_userName.c_str(), m_password.c_str());
	if(PQstatus(temp) == CONNECTION_BAD)
	{
		Log::Instance().OutError("PostgreSQLDatabase: Connection failed due to: `%s`", PQerrorMessage(temp));
		return false;
	}
	if(conn->conn != NULL)
		PQfinish(conn->conn);
	conn->conn = temp;
	return true;
}

PGresult* PostgreSQLDatabase::SendQuery(PConnection* con, const char* sql, bool self)
{
	PGresult* res = PQexec(con->conn, sql);
	ExecStatusType status = PQresultStatus(res);
	if(status == PGRES_BAD_RESPONSE)
	{
		if(!self)
		{
			Connect(con);
			return SendQuery(con, sql, true);
		}
		return NULL;
	}
	else if(status == PGRES_FATAL_ERROR)
	{
		Log::Instance().OutError("PostgreSQLDatabase: Sql query failed due to [%s], Query: [%s]\n",
			PQresultErrorMessage(res), sql);
		return NULL;
	}
	return res;
}

bool PostgreSQLDatabase::_Execute(PConnection* con, const char* sql)
{
	PGresult* res = SendQuery(con, sql, false);
	if(res == NULL)
		return false;
	PQclear(res);
	return true;
}

ResultPtr PostgreSQLDatabase::_Query(PConnection* con, const char* sql)
{
	ResultPtr qResult;
	PGresult* res = SendQuery(con, sql, false);
	if(res != NULL && PQresultStatus(res) == PGRES_TUPLES_OK)
	{
		uint32 size = PQntuples(res);
		if(size != 0)
			qResult.reset(new QueryResult(res, PQnfields(res), size));
	}
	return qResult;
}

std::string PostgreSQLDatabase::EscapeString(std::string str)
{
	size_t size = str.length();
	char* buffer = new char[size * 2 + 1];
	PConnection* con = GetFreeConnection();
	PQescapeStringConn(con->conn, buffer, str.c_str(), size, NULL);
	con->lock.unlock();
	std::string ret(buffer);
	delete[] buffer;
	return ret;
}