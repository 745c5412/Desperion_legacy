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

#ifndef __PARTY_UPDATE_COMMONS_INFORMATIONS__
#define __PARTY_UPDATE_COMMONS_INFORMATIONS__

class PartyUpdateCommonsInformations : public DofusModel
{
public:
	int lifePoints;
	int maxLifePoints;
	int16 prospecting;
	uint8 regenRate;

	uint16 GetProtocol() const
	{ return PARTY_UPDATE_COMMONS_INFORMATIONS; }

	PartyUpdateCommonsInformations()
	{
	}

	PartyUpdateCommonsInformations(int lifePoints, int maxLifePoints, int16 prospecting, uint8 regenRate) : lifePoints(lifePoints), maxLifePoints(maxLifePoints), prospecting(prospecting), regenRate(regenRate)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<lifePoints<<maxLifePoints<<prospecting<<regenRate;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>lifePoints>>maxLifePoints>>prospecting>>regenRate;
	}
};

typedef boost::shared_ptr<PartyUpdateCommonsInformations> PartyUpdateCommonsInformationsPtr;

#endif