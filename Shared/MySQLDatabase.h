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

#ifndef __MY_SQL_DATABASE__
#define __MY_SQL_DATABASE__

class MySQLDatabase : public Database<MYSQL>
{
private:
	bool SendQuery(MConnection*, const char*, bool);
	bool HandleError(MConnection*, uint32);
	bool Connect(MConnection*);
	bool _Execute(MConnection*, const char*);
	ResultPtr _Query(MConnection*, const char*);

public:
	MySQLDatabase(boost::asio::io_service& ios, size_t size)
		: Database<MYSQL>(ios, size)
	{
	}

	~MySQLDatabase();
	std::string EscapeString(std::string);
};

#endif