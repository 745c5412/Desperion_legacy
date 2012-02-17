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

#ifndef __PARTY_INVITATION_DUNGEON_DETAILS_MESSAGE__
#define __PARTY_INVITATION_DUNGEON_DETAILS_MESSAGE__

class PartyInvitationDungeonDetailsMessage : public PartyInvitationDetailsMessage
{
public:
	int16 dungeonId;
	std::vector<bool> playersDungeonReady;

	uint16 GetOpcode() const
	{ return SMSG_PARTY_INVITATION_DUNGEON_DETAILS; }

	PartyInvitationDungeonDetailsMessage()
	{
	}

	PartyInvitationDungeonDetailsMessage(int partyId, int8 partyType, int fromId, std::string fromName, int leaderId, std::vector<PartyInvitationMemberInformationsPtr>& members, int16 dungeonId, std::vector<bool>& playersDungeonReady) : PartyInvitationDetailsMessage(partyId, partyType, fromId, fromName, leaderId, members), dungeonId(dungeonId), playersDungeonReady(playersDungeonReady)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		PartyInvitationDetailsMessage::Serialize(data);
		data<<dungeonId;
		uint16 size = playersDungeonReady.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<playersDungeonReady[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		PartyInvitationDetailsMessage::Deserialize(data);
		data>>dungeonId;
		playersDungeonReady.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			bool val;
			data>>val;
			playersDungeonReady.push_back(val);
		}
	}
};

#endif