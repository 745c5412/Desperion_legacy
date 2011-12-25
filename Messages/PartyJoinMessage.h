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

#ifndef __PARTY_JOIN_MESSAGE__
#define __PARTY_JOIN_MESSAGE__

class PartyJoinMessage : public AbstractPartyMessage
{
public:
	int8 partyType;
	int partyLeaderId;
	int8 maxParticipants;
	std::vector<PartyMemberInformationsPtr> members;
	std::vector<PartyGuestInformationsPtr> guests;
	bool restricted;

	uint16 GetOpcode() const
	{ return SMSG_PARTY_JOIN; }

	PartyJoinMessage()
	{
	}

	PartyJoinMessage(int partyId, int8 partyType, int partyLeaderId, int8 maxParticipants, std::vector<PartyMemberInformationsPtr>& members, std::vector<PartyGuestInformationsPtr>& guests, bool restricted) : AbstractPartyMessage(partyId), partyType(partyType), partyLeaderId(partyLeaderId), maxParticipants(maxParticipants), members(members), guests(guests), restricted(restricted)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Serialize(data);
		data<<partyType<<partyLeaderId<<maxParticipants;
		uint16 size = members.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			members[a]->Serialize(data);
		uint16 size = guests.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			guests[a]->Serialize(data);
		data<<restricted;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Deserialize(data);
		data>>partyType>>partyLeaderId>>maxParticipants;
		members.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PartyMemberInformationsPtr model(new PartyMemberInformations);
			model->Deserialize(data);
			members.push_back(model);
		}
		guests.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PartyGuestInformationsPtr model(new PartyGuestInformations);
			model->Deserialize(data);
			guests.push_back(model);
		}
		data>>restricted;
	}
};

#endif