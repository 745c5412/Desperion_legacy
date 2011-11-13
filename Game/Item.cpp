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
	for(std::vector<EffectInstance*>::iterator it = m_possibleEffects.begin(); it != m_possibleEffects.end(); ++it)
	{
		if((*it)->IsDice()) // en theorie toujours des Dice dans d2o_item
		{
			EffectInstanceDice* effect = (EffectInstanceDice*)(*it);
			bool random;
			switch(effect->effectId)
			{
			case 98:
			case 81:
			case 82:
			case 84:
			case 91:
			case 92:
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 99:
			case 100:
			case 101:
			case 108:
			case 130:
			case 670:
			case 671:
			case 672:
			case 440:
			case 1012:
			case 1013:
			case 1014:
			case 1015:
			case 1016:
			case 1063:
			case 1064:
			case 1065:
			case 1066:
			case 1067:
			case 1068:
			case 1069:
			case 1070:
			case 1071:
				random = false;
				break;
			default:
				random = true;
				break;
			}
			if(random)
			{
				int value;
				if(effect->diceNum > effect->diceSide)
					value = effect->diceNum;
				else
				{
					if(max)
						value = effect->diceSide;
					else
						value = RandomUInt(effect->diceNum, effect->diceSide);
				}
				effects.push_back(new PlayerItemEffectInteger(effect->effectId, value));
			}
			else
				effects.push_back(new PlayerItemEffectDice(effect->effectId, effect->diceNum, effect->diceSide, 0));
		}
	}
	
	ResultPtr QR = Desperion::sDatabase->Query("SELECT effects FROM item_additional_effects WHERE id=%u LIMIT 1;", m_id);
	if(QR)
	{
		Field* fields = QR->Fetch();
		std::vector<PlayerItemEffect*> addEffects;
		Desperion::FastSplit<';'>(addEffects, std::string(fields[0].GetString()), G, true);
		time_t t = time(NULL);
		for(std::vector<PlayerItemEffect*>::iterator it = addEffects.begin(); it != addEffects.end(); ++it)
		{
			if((*it)->IsDate())
			{
				PlayerItemEffectDate* date = (PlayerItemEffectDate*)(*it);
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
			}
			effects.push_back(*it);
		}
	}
	
	
	item->Init(PlayerItem::GetNextItemGuid(), this, qua, INVENTORY_POSITION_NOT_EQUIPED, effects, owner);
	for(std::vector<PlayerItemEffect*>::iterator it = effects.begin(); it != effects.end(); ++it)
		delete *it;
	return item;
}

Item::~Item()
{
	for(std::vector<EffectInstance*>::iterator it = m_possibleEffects.begin(); it != m_possibleEffects.end(); ++it)
		delete *it;
}

void Item::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	m_typeId = fields[2].GetInt32();
	m_level = fields[5].GetInt32();
	m_weight = fields[6].GetInt32();
	m_cursed = fields[7].GetBool();
	m_useAnimationId = fields[8].GetInt32();
	m_usable = fields[9].GetBool();
	m_targetable = fields[10].GetBool();
	m_price = fields[11].GetInt32();
	m_twoHanded = fields[12].GetBool();
	m_etheral = fields[13].GetBool();
	m_itemSetId = fields[14].GetInt32();
	m_criteria = fields[15].GetString();
	m_appearanceId = fields[17].GetInt32();
	Desperion::FastSplit<';'>(m_possibleEffects, std::string(fields[20].GetString()), F);
	Desperion::FastSplit<','>(m_favoriteSubAreas, std::string(fields[21].GetString()), Desperion::SplitInt);
	m_favoriteSubAreaBonus = fields[22].GetInt32();
}