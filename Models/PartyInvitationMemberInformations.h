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

#ifndef __PARTY_INVITATION_MEMBER_INFORMATIONS__
#define __PARTY_INVITATION_MEMBER_INFORMATIONS__

class PartyInvitationMemberInformations : public CharacterBaseInformations
{
public:
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;

	uint16 GetProtocol() const
	{ return PARTY_INVITATION_MEMBER_INFORMATIONS; }

	PartyInvitationMemberInformations()
	{
	}

	PartyInvitationMemberInformations(int id, uint8 level, std::string name, EntityLook* entityLook, int8 breed, bool sex, int16 worldX, int16 worldY, int mapId, int16 subAreaId) : CharacterBaseInformations(id, level, name, entityLook, breed, sex), worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterBaseInformations::Serialize(data);
		data<<worldX<<worldY<<mapId<<subAreaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterBaseInformations::Deserialize(data);
		data>>worldX>>worldY>>mapId>>subAreaId;
	}
};

typedef boost::shared_ptr<PartyInvitationMemberInformations> PartyInvitationMemberInformationsPtr;

#endif