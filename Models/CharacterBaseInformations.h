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

#ifndef __CHARACTER_BASE_INFORMATIONS__
#define __CHARACTER_BASE_INFORMATIONS__

class CharacterBaseInformations : public CharacterMinimalPlusLookInformations
{
public:
	int8 breed;
	bool sex;

	uint16 GetProtocol() const
	{ return CHARACTER_BASE_INFORMATIONS; }

	CharacterBaseInformations()
	{
	}

	CharacterBaseInformations(int id, uint8 level, std::string name, EntityLook* entityLook, int8 breed, bool sex) : CharacterMinimalPlusLookInformations(id, level, name, entityLook), breed(breed), sex(sex)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterMinimalPlusLookInformations::Serialize(data);
		data<<breed<<sex;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterMinimalPlusLookInformations::Deserialize(data);
		data>>breed>>sex;
	}
};

typedef boost::shared_ptr<CharacterBaseInformations> CharacterBaseInformationsPtr;

#endif