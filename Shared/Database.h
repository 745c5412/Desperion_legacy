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


/*
	Based on AscentEmulator Database class
*/

struct Connection
{
	MYSQL* conn;
	boost::mutex lock;

	Connection()
	{
	}

	/*Connection(const Connection& that)
	{
	}*/
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
	ResultPtr StoreResult(Connection*);
	bool HandleError(Connection*, uint32);
	bool Reconnect(Connection*);
public:
	Database(uint8);
	~Database();

	std::string EscapeString(std::string);
	bool Init(std::string, uint16, std::string, std::string, std::string);
	ResultPtr Query(const char*, ...);
	bool Execute(const char*, ...);
};

#endif