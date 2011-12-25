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

#ifndef __PARTY_LOCATE_MEMBERS_MESSAGE__
#define __PARTY_LOCATE_MEMBERS_MESSAGE__

class PartyLocateMembersMessage : public AbstractPartyMessage
{
public:
	std::vector<PartyMemberGeoPositionPtr> geopositions;

	uint16 GetOpcode() const
	{ return SMSG_PARTY_LOCATE_MEMBERS; }

	PartyLocateMembersMessage()
	{
	}

	PartyLocateMembersMessage(int partyId, std::vector<PartyMemberGeoPositionPtr>& geopositions) : AbstractPartyMessage(partyId), geopositions(geopositions)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Serialize(data);
		uint16 size = geopositions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			geopositions[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Deserialize(data);
		geopositions.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PartyMemberGeoPositionPtr model(new PartyMemberGeoPosition);
			model->Deserialize(data);
			geopositions.push_back(model);
		}
	}
};

#endif