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

#ifndef __FIGHT_ENTITY_DISPOSITION_INFORMATIONS__
#define __FIGHT_ENTITY_DISPOSITION_INFORMATIONS__

class FightEntityDispositionInformations : public EntityDispositionInformations
{
public:
	int carryingCharacterId;

	uint16 GetProtocol() const
	{ return FIGHT_ENTITY_DISPOSITION_INFORMATIONS; }

	FightEntityDispositionInformations()
	{
	}

	FightEntityDispositionInformations(int16 cellId, int8 direction, int carryingCharacterId) : EntityDispositionInformations(cellId, direction), carryingCharacterId(carryingCharacterId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		EntityDispositionInformations::Serialize(data);
		data<<carryingCharacterId;
	}

	void Deserialize(ByteBuffer& data)
	{
		EntityDispositionInformations::Deserialize(data);
		data>>carryingCharacterId;
	}
};

typedef boost::shared_ptr<FightEntityDispositionInformations> FightEntityDispositionInformationsPtr;

#endif