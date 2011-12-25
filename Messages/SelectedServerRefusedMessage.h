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

#ifndef __SELECTED_SERVER_REFUSED_MESSAGE__
#define __SELECTED_SERVER_REFUSED_MESSAGE__

enum ServerConnectionError
{
	SERVER_CONNECTION_ERROR_DUE_TO_STATUS = 0,
	SERVER_CONNECTION_ERROR_NO_REASON = 1,
	SERVER_CONNECTION_ERROR_ACCOUNT_RESTRICTED = 2,
	SERVER_CONNECTION_ERROR_COMMUNITY_RESTRICTED = 3,
	SERVER_CONNECTION_ERROR_LOCATION_RESTRICTED = 4,
	SERVER_CONNECTION_ERROR_SUBSCRIBERS_ONLY = 5,
	SERVER_CONNECTION_ERROR_REGULAR_PLAYERS_ONLY = 6,
};

class SelectedServerRefusedMessage : public DofusMessage
{
public:
	int16 serverId;
	int8 error;
	int8 serverStatus;

	uint16 GetOpcode() const
	{ return SMSG_SELECTED_SERVER_REFUSED; }

	SelectedServerRefusedMessage()
	{
	}

	SelectedServerRefusedMessage(int16 serverId, int8 error, int8 serverStatus) : serverId(serverId), error(error), serverStatus(serverStatus)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<serverId<<error<<serverStatus;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>serverId>>error>>serverStatus;
	}
};

#endif