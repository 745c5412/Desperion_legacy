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

#ifndef __ABSTRACT_PARTY_EVENT_MESSAGE__
#define __ABSTRACT_PARTY_EVENT_MESSAGE__

class AbstractPartyEventMessage : public AbstractPartyMessage
{
public:

	uint16 GetOpcode() const
	{ return SMSG_ABSTRACT_PARTY_EVENT; }

	AbstractPartyEventMessage()
	{
	}

	AbstractPartyEventMessage(int partyId) : AbstractPartyMessage(partyId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Deserialize(data);
	}
};

#endif