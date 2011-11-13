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

#ifndef __CHARACTER_MINIMALS__
#define __CHARACTER_MINIMALS__

class Character;

struct DEntityLook
{
	int16 bonesId;
	std::vector<int16> skins;
	std::vector<int> indexedColors;
	std::vector<int16> scales;

	void Init(std::string str)
	{
		std::vector<std::string> table;
		Desperion::FastSplitString<';'>(table, str, true);

		bonesId = atoi(table.at(0).c_str());
		Desperion::FastSplit<','>(skins, table[1], Desperion::SplitInt, true);
		Desperion::FastSplit<','>(indexedColors, table[2], Desperion::SplitInt, true);
		Desperion::FastSplit<','>(scales, table[3], Desperion::SplitInt, true);
	}

	std::string ToString()
	{
		std::ostringstream str;
		str<<bonesId<<";";
		for(size_t a = 0; a < skins.size(); ++a)
		{
			if(a != 0)
				str<<",";
			str<<skins[a];
		}
		str<<";";
		for(size_t a = 0; a < indexedColors.size(); ++a)
		{
			if(a != 0)
				str<<",";
			str<<indexedColors[a];
		}
		str<<";";
		for(size_t a = 0; a < scales.size(); ++a)
		{
			if(a != 0)
				str<<",";
			str<<scales[a];
		}
		return str.str();
	}
};

class EntityLook;

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

	EntityLook* GetLook() const;

	void Init(Field* fields)
	{
		id = fields[0].GetInt32();
		level = fields[1].GetUInt8();
		name = fields[2].GetString();
		look.Init(fields[3].GetString());
		breed = fields[4].GetInt8();
		sex = fields[5].GetBool();
		account = fields[6].GetInt32();
		onlineCharacter = NULL;
	}
};

#endif