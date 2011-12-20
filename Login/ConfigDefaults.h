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

#ifndef __CONFIG_DEFAULTS__
#define __CONFIG_DEFAULTS__

//------------------------------------
// SERVER.PROPERTIES
//------------------------------------

#define LOCAL_DATABASE_HOST_STRING "LocalDatabaseHost"
#define LOCAL_DATABASE_HOST_DEFAULT "127.0.0.1"

#define LOCAL_DATABASE_NAME_STRING "LocalDatabaseName"
#define LOCAL_DATABASE_NAME_DEFAULT "desperion"

#define LOCAL_DATABASE_USER_STRING "LocalDatabaseUser"
#define LOCAL_DATABASE_USER_DEFAULT "root"

#define LOCAL_DATABASE_PASSWORD_STRING "LocalDatabasePassword"
#define LOCAL_DATABASE_PASSWORD_DEFAULT ""

#define LOCAL_DATABASE_PORT_STRING "LocalDatabasePort"
#define LOCAL_DATABASE_PORT_DEFAULT 3306

#define LOCAL_SERVER_PORT_STRING "LocalServerPort"
#define LOCAL_SERVER_PORT_DEFAULT 443

#define DISTANT_SERVER_PORT_STRING "DistantServerPort"
#define DISTANT_SERVER_PORT_DEFAULT 444

//------------------------------------
// MISC.PROPERTIES
//------------------------------------

#define SERVER_MAINTENANCE_STRING "ServerMaintenance"
#define SERVER_MAINTENANCE_DEFAULT false

#define LOGS_PATH_STRING "LogsPath"
#define LOGS_PATH_DEFAULT "logs"

#define LOGS_LEVEL_STRING "LogsLevel"
#define LOGS_LEVEL_DEFAULT 0xff

#define PRIV_FILE_PATH_STRING "PrivFilePath"
#define PRIV_FILE_PATH_DEFAULT "priv.der"

#define PUB_FILE_PATH_STRING "PubFilePath"
#define PUB_FILE_PATH_DEFAULT "pub.der"

#endif