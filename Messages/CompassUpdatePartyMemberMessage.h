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

#ifndef __COMPASS_UPDATE_PARTY_MEMBER_MESSAGE__
#define __COMPASS_UPDATE_PARTY_MEMBER_MESSAGE__

class CompassUpdatePartyMemberMessage : public CompassUpdateMessage
{
public:
	int memberId;

	uint16 GetOpcode() const
	{ return SMSG_COMPASS_UPDATE_PARTY_MEMBER; }

	CompassUpdatePartyMemberMessage()
	{
	}

	CompassUpdatePartyMemberMessage(int8 type, int16 worldX, int16 worldY, int memberId) : CompassUpdateMessage(type, worldX, worldY), memberId(memberId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		CompassUpdateMessage::Serialize(data);
		data<<memberId;
	}

	void Deserialize(ByteBuffer& data)
	{
		CompassUpdateMessage::Deserialize(data);
		data>>memberId;
	}
};

#endif