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

#ifndef __FRIEND_INFORMATIONS__
#define __FRIEND_INFORMATIONS__

class FriendInformations : public AbstractContactInformations
{
public:
	int8 playerState;
	int lastConnection;

	uint16 GetProtocol() const
	{ return FRIEND_INFORMATIONS; }

	FriendInformations()
	{
	}

	FriendInformations(int accountId, std::string accountName, int8 playerState, int lastConnection) : AbstractContactInformations(accountId, accountName), playerState(playerState), lastConnection(lastConnection)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractContactInformations::Serialize(data);
		data<<playerState<<lastConnection;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractContactInformations::Deserialize(data);
		data>>playerState>>lastConnection;
	}
};

typedef boost::shared_ptr<FriendInformations> FriendInformationsPtr;

#endif