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

#include "StdAfx.h"

void Item::InitFavoriteSubAreas(std::string subareas)
{
	ByteBuffer buffer = Desperion::DbToBuffer(subareas);
	uint16 size;
	buffer>>size;
	for(uint16 a = 0; a < size; ++a)
	{
		int area;
		buffer>>area;
		m_favoriteSubAreas.push_back(area);
	}
}

void Item::InitPossibleEffects(std::string effects)
{
	ByteBuffer buffer = Desperion::DbToBuffer(effects);
	uint16 size;
	buffer>>size;
	for(uint16 a = 0; a < size; ++a)
	{
		EffectInstanceDice i;
		buffer>>i.effectId>>i.diceNum>>i.duration>>i.hidden>>i.diceSide>>i.value>>i.random>>i.targetId>>i.zoneSize>>i.zoneShape;
		m_possibleEffects.push_back(i);
	}
}

void Item::_Init(int16 id, int typeId, int level, int weight, bool cursed, int useAnimationId, bool usable,
		bool targetable, int price, bool twoHanded, bool etheral, int itemSetId, std::string criteria,
		int appearanceId, std::string possibleEffects, std::string favoriteSubAreas, int favoriteSubAreaBonus)
{
	m_id = id;
	m_typeId = typeId;
	m_level = level;
	m_weight = weight;
	m_cursed = cursed;
	m_useAnimationId = useAnimationId;
	m_usable = usable;
	m_targetable = targetable;
	m_price = price;
	m_twoHanded = twoHanded;
	m_etheral = etheral;
	m_itemSetId = itemSetId;
	m_criteria = criteria;
	m_appearanceId = appearanceId;
	InitPossibleEffects(possibleEffects);
	InitFavoriteSubAreas(favoriteSubAreas);
	m_favoriteSubAreaBonus = favoriteSubAreaBonus;
}

void Item::Init(Field* fields)
{
	_Init(fields[0].GetInt16(), fields[2].GetInt32(), fields[5].GetInt32(), fields[6].GetInt32(), fields[7].GetBool(), fields[8].GetInt32(),
		fields[9].GetBool(), fields[10].GetBool(), fields[11].GetInt32(), fields[12].GetBool(), fields[13].GetBool(), fields[14].GetInt32(),
		fields[15].GetString(), fields[17].GetInt32(), fields[20].GetString(), fields[21].GetString(), fields[22].GetInt32());
}