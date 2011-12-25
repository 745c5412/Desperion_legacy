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

#ifndef __PARTY_MEMBER_INFORMATIONS__
#define __PARTY_MEMBER_INFORMATIONS__

class PartyMemberInformations : public CharacterMinimalPlusLookInformations
{
public:
	int lifePoints;
	int maxLifePoints;
	int16 prospecting;
	uint8 regenRate;
	int16 initiative;
	bool pvpEnabled;
	int8 alignmentSide;

	uint16 GetProtocol() const
	{ return PARTY_MEMBER_INFORMATIONS; }

	PartyMemberInformations()
	{
	}

	PartyMemberInformations(int id, uint8 level, std::string name, EntityLook* entityLook, int lifePoints, int maxLifePoints, int16 prospecting, uint8 regenRate, int16 initiative, bool pvpEnabled, int8 alignmentSide) : CharacterMinimalPlusLookInformations(id, level, name, entityLook), lifePoints(lifePoints), maxLifePoints(maxLifePoints), prospecting(prospecting), regenRate(regenRate), initiative(initiative), pvpEnabled(pvpEnabled), alignmentSide(alignmentSide)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		CharacterMinimalPlusLookInformations::Serialize(data);
		data<<lifePoints<<maxLifePoints<<prospecting<<regenRate<<initiative<<pvpEnabled<<alignmentSide;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterMinimalPlusLookInformations::Deserialize(data);
		data>>lifePoints>>maxLifePoints>>prospecting>>regenRate>>initiative>>pvpEnabled>>alignmentSide;
	}
};

typedef boost::shared_ptr<PartyMemberInformations> PartyMemberInformationsPtr;

#endif