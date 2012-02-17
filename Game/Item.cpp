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

PlayerItem* Item::Create(int qua, bool max, Character* owner)
{
	PlayerItem* item = new PlayerItem;
	std::vector<PlayerItemEffect*> effects;
	time_t t = time(NULL);
	for(std::vector<PlayerItemEffect*>::iterator it = m_possibleEffects.begin(); it != m_possibleEffects.end(); ++it)
	{
		if((*it)->IsMinMax())
		{
			int value;
			PlayerItemEffectMinMax* effect = (PlayerItemEffectMinMax*)(*it);
			if(effect->min)
				value = effect->min;
			else
			{
				if(max)
					value = effect->max;
				else
					value = RandomUInt(effect->min, effect->max);
			}
			effects.push_back(new PlayerItemEffectInteger(effect->actionId, value));
		}
		else if((*it)->IsDice() && ((PlayerItemEffectDice*)(*it))->diceConst != 0)
		{
			PlayerItemEffectDice* effect = (PlayerItemEffectDice*)(*it);
			effects.push_back(new PlayerItemEffectMinMax(effect->actionId, effect->diceNum, effect->diceSide));
		}
		else if((*it)->IsDate())
		{
			PlayerItemEffectDate* date = (PlayerItemEffectDate*)(*it);
			date->actionId = (*it)->actionId;
			struct tm* tm = localtime(&t);
			date->year = tm->tm_year; // 0 = 1900
			date->month += tm->tm_mon; // 0-11
			date->day = tm->tm_mday; // 1-31
			date->hour = tm->tm_hour; // 0-23
			date->minute = tm->tm_min; // 0-59
			while(date->month > 11)
			{
				date->month -= 11;
				++date->year;
			}
			effects.push_back(date->Clone());
		}
		else
			effects.push_back((*it)->Clone());
	}
	
	item->Init(World::Instance().GetNextItemGuid(), this, qua, INVENTORY_POSITION_NOT_EQUIPED, effects, owner);
	for(std::vector<PlayerItemEffect*>::iterator it = effects.begin(); it != effects.end(); ++it)
		delete *it;
	return item;
}

Item::~Item()
{
	for(std::vector<PlayerItemEffect*>::iterator it = m_possibleEffects.begin(); it != m_possibleEffects.end(); ++it)
		delete *it;
}

void Item::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	m_typeId = fields[1].GetInt32();
	m_level = fields[2].GetInt32();
	m_weight = fields[3].GetInt32();
	m_cursed = fields[4].GetBool();
	m_useAnimationId = fields[5].GetInt32();
	m_usable = fields[6].GetBool();
	m_targetable = fields[7].GetBool();
	m_price = fields[8].GetInt64();
	m_twoHanded = fields[9].GetBool();
	m_etheral = fields[10].GetBool();
	m_itemSetId = fields[11].GetInt32();
	m_criteria = fields[12].GetString();
	m_appearanceId = fields[13].GetInt32();
	Desperion::FastSplit<';'>(m_possibleEffects, std::string(fields[14].GetString()), G);
	Desperion::FastSplit<','>(m_favoriteSubAreas, std::string(fields[15].GetString()), Desperion::SplitInt);
	m_favoriteSubAreaBonus = fields[16].GetInt32();
}