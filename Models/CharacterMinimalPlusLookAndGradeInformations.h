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

#ifndef __CHARACTER_MINIMAL_PLUS_LOOK_AND_GRADE_INFORMATIONS__
#define __CHARACTER_MINIMAL_PLUS_LOOK_AND_GRADE_INFORMATIONS__

class CharacterMinimalPlusLookAndGradeInformations : public CharacterMinimalPlusLookInformations
{
public:
	int grade;

	uint16 GetProtocol() const
	{ return CHARACTER_MINIMAL_PLUS_LOOK_AND_GRADE_INFORMATIONS; }

	CharacterMinimalPlusLookAndGradeInformations()
	{
	}

	CharacterMinimalPlusLookAndGradeInformations(int id, uint8 level, std::string name, EntityLook* entityLook, int grade) : CharacterMinimalPlusLookInformations(id, level, name, entityLook), grade(grade)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterMinimalPlusLookInformations::Serialize(data);
		data<<grade;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterMinimalPlusLookInformations::Deserialize(data);
		data>>grade;
	}
};

typedef boost::shared_ptr<CharacterMinimalPlusLookAndGradeInformations> CharacterMinimalPlusLookAndGradeInformationsPtr;

#endif