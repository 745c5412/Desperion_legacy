/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __CHARACTER_MINIMALS__
#define __CHARACTER_MINIMALS__

struct DEntityLook;
class Character;

struct DSubEntity
{
	int8 bindingPointCategory;
	int8 bindingPointIndex;
	DEntityLook* subEntityLook;

	void Init(ByteBuffer& buffer);
	ByteBuffer Serialize() const;
	~DSubEntity();
};

struct DEntityLook
{
	int16 bonesId;
	std::vector<int16> skins;
	std::vector<int> indexedColors;
	std::vector<int16> scales;
	std::vector<DSubEntity> subentities;

	void Init(ByteBuffer& buffer)
	{
		buffer>>bonesId;
		uint16 size;
		buffer>>size;
		for(int a = 0; a < size; ++a)
		{
			int16 skin;
			buffer>>skin;
			skins.push_back(skin);
		}
		buffer>>size;
		for(int a = 0; a < size; ++a)
		{
			int color;
			buffer>>color;
			indexedColors.push_back(color);
		}
		buffer>>size;
		for(int a = 0; a < size; ++a)
		{
			int16 scale;
			buffer>>scale;
			scales.push_back(scale);
		}
		buffer>>size;
		for(int a = 0; a < size; ++a)
		{
			DSubEntity sub;
			sub.Init(buffer);
			subentities.push_back(sub);
		}
	}

	std::vector<int16> GetSkins() const;
	ByteBuffer Serialize(int) const;
	ByteBuffer Serialize(Character*) const;
	ByteBuffer Serialize(const std::vector<int16>&, const std::vector<int16>&) const;
};

struct CharacterMinimals
{
	int id;
	uint8 level;
	std::string name;
	DEntityLook look;
	int8 breed;
	bool sex;
	int account;
	Character* onlineCharacter;

	void Init(Field* fields)
	{
		id = fields[0].GetInt32();
		level = fields[1].GetUInt8();
		name = fields[2].GetString();
		look.Init(Desperion::DbToBuffer(fields[3].GetString()));
		breed = fields[4].GetInt8();
		sex = fields[5].GetBool();
		account = fields[6].GetInt32();
		onlineCharacter = NULL;
	}

	ByteBuffer Serialize() const;
};

#endif