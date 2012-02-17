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

#ifndef __CHARACTER_LEVEL_UP_INFORMATION_MESSAGE__
#define __CHARACTER_LEVEL_UP_INFORMATION_MESSAGE__

class CharacterLevelUpInformationMessage : public CharacterLevelUpMessage
{
public:
	std::string name;
	int id;
	int8 relationType;

	uint16 GetOpcode() const
	{ return SMSG_CHARACTER_LEVEL_UP_INFORMATION; }

	CharacterLevelUpInformationMessage()
	{
	}

	CharacterLevelUpInformationMessage(uint8 newLevel, std::string name, int id, int8 relationType) : CharacterLevelUpMessage(newLevel), name(name), id(id), relationType(relationType)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterLevelUpMessage::Serialize(data);
		data<<name<<id<<relationType;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterLevelUpMessage::Deserialize(data);
		data>>name>>id>>relationType;
	}
};

#endif