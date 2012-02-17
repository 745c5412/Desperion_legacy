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

#ifndef __CHARACTER_HARDCORE_INFORMATIONS__
#define __CHARACTER_HARDCORE_INFORMATIONS__

class CharacterHardcoreInformations : public CharacterBaseInformations
{
public:
	int8 deathState;
	int16 deathCount;
	uint8 deathMaxLevel;

	uint16 GetProtocol() const
	{ return CHARACTER_HARDCORE_INFORMATIONS; }

	CharacterHardcoreInformations()
	{
	}

	CharacterHardcoreInformations(int id, uint8 level, std::string name, EntityLook* entityLook, int8 breed, bool sex, int8 deathState, int16 deathCount, uint8 deathMaxLevel) : CharacterBaseInformations(id, level, name, entityLook, breed, sex), deathState(deathState), deathCount(deathCount), deathMaxLevel(deathMaxLevel)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterBaseInformations::Serialize(data);
		data<<deathState<<deathCount<<deathMaxLevel;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterBaseInformations::Deserialize(data);
		data>>deathState>>deathCount>>deathMaxLevel;
	}
};

typedef boost::shared_ptr<CharacterHardcoreInformations> CharacterHardcoreInformationsPtr;

#endif