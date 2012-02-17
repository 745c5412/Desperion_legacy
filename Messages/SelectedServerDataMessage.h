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

#ifndef __SELECTED_SERVER_DATA_MESSAGE__
#define __SELECTED_SERVER_DATA_MESSAGE__

class SelectedServerDataMessage : public DofusMessage
{
public:
	int16 serverId;
	std::string address;
	uint16 port;
	bool canCreateNewCharacter;
	std::string ticket;

	uint16 GetOpcode() const
	{ return SMSG_SELECTED_SERVER_DATA; }

	SelectedServerDataMessage()
	{
	}

	SelectedServerDataMessage(int16 serverId, std::string address, uint16 port, bool canCreateNewCharacter, std::string ticket) : serverId(serverId), address(address), port(port), canCreateNewCharacter(canCreateNewCharacter), ticket(ticket)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<serverId<<address<<port<<canCreateNewCharacter<<ticket;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>serverId>>address>>port>>canCreateNewCharacter>>ticket;
	}
};

#endif