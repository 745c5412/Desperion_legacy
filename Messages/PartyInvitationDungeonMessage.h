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

#ifndef __PARTY_INVITATION_DUNGEON_MESSAGE__
#define __PARTY_INVITATION_DUNGEON_MESSAGE__

class PartyInvitationDungeonMessage : public PartyInvitationMessage
{
public:
	int16 dungeonId;

	uint16 GetOpcode() const
	{ return SMSG_PARTY_INVITATION_DUNGEON; }

	PartyInvitationDungeonMessage()
	{
	}

	PartyInvitationDungeonMessage(int partyId, int8 partyType, int8 maxParticipants, int fromId, std::string fromName, int toId, int16 dungeonId) : PartyInvitationMessage(partyId, partyType, maxParticipants, fromId, fromName, toId), dungeonId(dungeonId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		PartyInvitationMessage::Serialize(data);
		data<<dungeonId;
	}

	void Deserialize(ByteBuffer& data)
	{
		PartyInvitationMessage::Deserialize(data);
		data>>dungeonId;
	}
};

#endif