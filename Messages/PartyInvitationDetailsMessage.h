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

#ifndef __PARTY_INVITATION_DETAILS_MESSAGE__
#define __PARTY_INVITATION_DETAILS_MESSAGE__

class PartyInvitationDetailsMessage : public AbstractPartyMessage
{
public:
	int8 partyType;
	int fromId;
	std::string fromName;
	int leaderId;
	std::vector<PartyInvitationMemberInformationsPtr> members;

	uint16 GetOpcode() const
	{ return SMSG_PARTY_INVITATION_DETAILS; }

	PartyInvitationDetailsMessage()
	{
	}

	PartyInvitationDetailsMessage(int partyId, int8 partyType, int fromId, std::string fromName, int leaderId, std::vector<PartyInvitationMemberInformationsPtr>& members) : AbstractPartyMessage(partyId), partyType(partyType), fromId(fromId), fromName(fromName), leaderId(leaderId), members(members)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractPartyMessage::Serialize(data);
		data<<partyType<<fromId<<fromName<<leaderId;
		uint16 size = members.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<members[a]->GetProtocol();
			members[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Deserialize(data);
		data>>partyType>>fromId>>fromName>>leaderId;
		members.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			PartyInvitationMemberInformationsPtr model(Desperion::ProtocolTypeManager::GetPartyInvitationMemberInformations(protocol));
			model->Deserialize(data);
			members.push_back(model);
		}
	}
};

#endif