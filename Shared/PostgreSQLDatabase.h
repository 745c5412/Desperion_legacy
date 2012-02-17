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

#ifndef __POSTGRE_SQL_DATABASE__
#define __POSTGRE_SQL_DATABASE__

class PostgreSQLDatabase : public Database<PGconn>
{
private:
	PGresult* SendQuery(PConnection*, const char*, bool);
	bool HandleError(PConnection*, uint32);
	bool Connect(PConnection*);
	bool _Execute(PConnection*, const char*);
	ResultPtr _Query(PConnection*, const char*);

public:
	PostgreSQLDatabase(boost::asio::io_service& ios, size_t size)
		: Database<PGconn>(ios, size)
	{
	}

	~PostgreSQLDatabase();
	std::string EscapeString(std::string);
};

#endif