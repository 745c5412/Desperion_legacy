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
#define LOCAL_DATABASE_NAME_DEFAULT "desperion-game"

#define LOCAL_DATABASE_USER_STRING "LocalDatabaseUser"
#define LOCAL_DATABASE_USER_DEFAULT "root"

#define LOCAL_DATABASE_PASSWORD_STRING "LocalDatabasePassword"
#define LOCAL_DATABASE_PASSWORD_DEFAULT ""

#define LOCAL_DATABASE_PORT_STRING "LocalDatabasePort"
#define LOCAL_DATABASE_PORT_DEFAULT 3306

#define DISTANT_DATABASE_HOST_STRING "DistantDatabaseHost"
#define DISTANT_DATABASE_HOST_DEFAULT "127.0.0.1"

#define DISTANT_DATABASE_NAME_STRING "DistantDatabaseName"
#define DISTANT_DATABASE_NAME_DEFAULT "desperion"

#define DISTANT_DATABASE_USER_STRING "DistantDatabaseUser"
#define DISTANT_DATABASE_USER_DEFAULT "root"

#define DISTANT_DATABASE_PASSWORD_STRING "DistantDatabasePassword"
#define DISTANT_DATABASE_PASSWORD_DEFAULT ""

#define DISTANT_DATABASE_PORT_STRING "DistantDatabasePort"
#define DISTANT_DATABASE_PORT_DEFAULT 3306

#define LOCAL_SERVER_PORT_STRING "LocalServerPort"
#define LOCAL_SERVER_PORT_DEFAULT 5555

#define DISTANT_SERVER_PORT_STRING "DistantServerPort"
#define DISTANT_SERVER_PORT_DEFAULT 444

#define DISTANT_SERVER_HOST_STRING "DistantServerHost"
#define DISTANT_SERVER_HOST_DEFAULT "127.0.0.1"

#define LOCAL_SERVER_AUTH_KEY_STRING "LocalServerAuthKey"
#define LOCAL_SERVER_AUTH_KEY_DEFAULT "default"

#define LOCAL_SERVER_ID_STRING "LocalServerID"
#define LOCAL_SERVER_ID_DEFAULT 1

#define LOGS_PATH_STRING "LogsPath"
#define LOGS_PATH_DEFAULT "logs"

#define LOGS_LEVEL_STRING "LogsLevel"
#define LOGS_LEVEL_DEFAULT 0xff


//------------------------------------
// CHARACTER.PROPERTIES
//------------------------------------

#define MAX_AP_STRING "MaxAP"
#define MAX_AP_DEFAULT 12

#define MAX_MP_STRING "MaxMP"
#define MAX_MP_DEFAULT 6

#define MAX_RANGE_STRING "MaxRange"
#define MAX_RANGE_DEFAULT 9

#define MAX_EXOTIC_AP_STRING "MaxExoticAP"
#define MAX_EXOTIC_AP_DEFAULT 1

#define MAX_EXOTIC_MP_STRING "MaxExoticMP"
#define MAX_EXOTIC_MP_DEFAULT 1

#define MAX_EXOTIC_RANGE_STRING "MaxExoticRange"
#define MAX_EXOTIC_RANGE_DEFAULT 1

#define START_LEVEL_STRING "StartLevel"
#define START_LEVEL_DEFAULT 1

#define START_KAMAS_STRING "StartKamas"
#define START_KAMAS_DEFAULT 0

#define START_SPELL_BOOST_STRING "StartSpellBoost"
#define START_SPELL_BOOST_DEFAULT 0

#define START_CAPITAL_STRING "StartCapital"
#define START_CAPITAL_DEFAULT 0

#define FULL_SCROLLED_STRING "FullScrolled"
#define FULL_SCROLLED_DEFAULT false

#define CUSTOM_START_MAP_STRING "CustomStartMap"
#define CUSTOM_START_MAP_DEFAULT 81269763

#define CUSTOM_START_CELL_STRING "CustomStartCell"
#define CUSTOM_START_CELL_DEFAULT 314

#define MAX_CHARACTERS_COUNT_STRING "MaxCharactersCount"
#define MAX_CHARACTERS_COUNT_DEFAULT 5

#define START_ZAAPS_STRING "StartZaaps"
#define START_ZAAPS_DEFAULT ""

#define START_EMOTES_STRING "StartEmotes"
#define START_EMOTES_DEFAULT "1"

#define START_ITEMS_STRING "StartItems"
#define START_ITEMS_DEFAULT ""


//------------------------------------
// MISC.PROPERTIES
//------------------------------------

#define SIT_REGEN_TIMER_STRING "SitRegenTimer"
#define SIT_REGEN_TIMER_DEFAULT 1000

#define STAND_REGEN_TIMER_STRING "StandRegenTimer"
#define STAND_REGEN_TIMER_DEFAULT 2000

#define NAME_SUGGESTION_RETRY_TIME_STRING "NameSuggestionRetryTime"
#define NAME_SUGGESTION_RETRY_TIME_DEFAULT 500

#define EXPERIENCE_FACTOR_STRING "ExperienceFactor"
#define EXPERIENCE_FACTOR_DEFAULT 1

#define USE_WEIGHT_LIMIT_STRING "UseWeightLimit"
#define USE_WEIGHT_LIMIT_DEFAULT true

#endif