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

Mutex PlayerItem::m_guidLock;

void PlayerItem::Init(Field* fields)
{
	m_guid = fields[0].GetInt32();
	m_item = World::Instance().GetItem(fields[1].GetInt32());
	m_quantity = fields[2].GetInt32();
	CharacterMinimals* ch = World::Instance().GetCharacterMinimals(fields[5].GetInt32());
	m_owner = (ch ? ch->onlineCharacter : NULL);
	Desperion::FastSplit<';'>(m_effects, std::string(fields[4].GetString()), G, true);
	m_pos = INVENTORY_POSITION_NOT_EQUIPED;
	SetPos(fields[3].GetUInt8());
}

void PlayerItem::Init(int guid, const Item* item, int qua, uint8 pos, const std::vector<PlayerItemEffect*>& effects, Character* owner)
{
	m_guid = guid;
	m_item = const_cast<Item*>(item);
	m_quantity = qua;
	for(std::vector<PlayerItemEffect*>::const_iterator it = effects.begin(); it != effects.end(); ++it)
		m_effects.push_back((*it)->Clone());
	m_owner = owner;
	m_pos = INVENTORY_POSITION_NOT_EQUIPED;
	SetPos(pos);
}

void PlayerItem::SetPos(int pos)
{
	if(m_pos == pos)
		return;

	if(m_pos == INVENTORY_POSITION_NOT_EQUIPED && pos != INVENTORY_POSITION_NOT_EQUIPED && m_owner)
	{
		for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			m_owner->ApplyEffect(&StatsRow::objects, (*it)->actionId, ((PlayerItemEffectInteger*)*it)->value, true);
	}
	else if(m_pos != INVENTORY_POSITION_NOT_EQUIPED && pos == INVENTORY_POSITION_NOT_EQUIPED && m_owner)
	{
		for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			m_owner->ApplyEffect(&StatsRow::objects, (*it)->actionId, ((PlayerItemEffectInteger*)*it)->value, false);
	}
	
	m_pos = pos;
}

ObjectItem* PlayerItem::ToObjectItem() const
{ 
	std::vector<ObjectEffectPtr> effects;
	for(std::vector<PlayerItemEffect*>::const_iterator it = m_effects.begin(); it != m_effects.end(); ++it)
		effects.push_back(ObjectEffectPtr((*it)->ToObjectEffect()));
	return new ObjectItem(m_pos, m_item->GetId(), 0, false, effects, m_guid, m_quantity);
}

int PlayerItem::GetNextItemGuid()
{
	int guid = 1;
	m_guidLock.lock();
	ResultPtr QR = Desperion::sDatabase.Query("SELECT guid FROM character_items ORDER BY guid DESC;");
	if(QR)
		guid = (QR->Fetch()[0].GetInt32()) + 1;
	
	m_guidLock.unlock();
	return guid;
}

void PlayerItem::InsertIntoDB(PlayerItem* item)
{
	Desperion::sDatabase.Execute("INSERT INTO character_items VALUES(%u, %u, %u, %u, '%s', %u);", item->GetGuid(),
		item->GetItem()->GetId(), item->GetQuantity(), item->GetPos(), item->StatsToString().c_str(), 
		item->GetOwner() ? item->GetOwner()->GetGuid() : 0);
}

bool PlayerItem::SameStats(PlayerItem* i1, PlayerItem* i2)
{
	typedef std::vector<PlayerItemEffect*> E;
	const E& e1 = i1->GetEffects();
	const E& e2 = i2->GetEffects();
	if(e1.size() != e2.size())
		return false;
	E::const_iterator f1 = e1.begin(), f2 = e2.begin(), l1 = e1.end();
	for(; f1 != l1; ++f1, ++f2)
	{
		if((*f1)->actionId != (*f2)->actionId)
			return false;
		else if((*f1)->IsInteger())
		{
			if(!(*f2)->IsInteger())
				return false;
			PlayerItemEffectInteger* ff1 = (PlayerItemEffectInteger*)(*f1), 
				* ff2 = (PlayerItemEffectInteger*)(*f2);
			if(ff1->value != ff2->value)
				return false;
		}
		else if((*f1)->IsDice())
		{
			if(!(*f2)->IsDice())
				return false;
			PlayerItemEffectDice* ff1 = (PlayerItemEffectDice*)(*f1), 
				* ff2 = (PlayerItemEffectDice*)(*f2);
			if(ff1->diceConst != ff2->diceConst || ff1->diceNum != ff2->diceNum
				|| ff1->diceSide != ff2->diceSide)
				return false;
		}
		else if((*f1)->IsCreature())
		{
			if(!(*f2)->IsCreature())
				return false;
			PlayerItemEffectCreature* ff1 = (PlayerItemEffectCreature*)(*f1), 
				* ff2 = (PlayerItemEffectCreature*)(*f2);
			if(ff1->monsterFamilyId != ff2->monsterFamilyId)
				return false;
		}
		else if((*f1)->IsDate())
		{
			if(!(*f2)->IsDate())
				return false;
			PlayerItemEffectDate* ff1 = (PlayerItemEffectDate*)(*f1), 
				* ff2 = (PlayerItemEffectDate*)(*f2);
			if(ff1->year != ff2->year || ff1->month != ff2->month
				|| ff1->day != ff2->day || ff1->hour != ff2->hour
				|| ff1->minute != ff2->minute)
				return false;
		}
		else if((*f1)->IsDuration())
		{
			if(!(*f2)->IsDuration())
				return false;
			PlayerItemEffectDuration* ff1 = (PlayerItemEffectDuration*)(*f1), 
				* ff2 = (PlayerItemEffectDuration*)(*f2);
			if(ff1->days != ff2->days || ff1->hours != ff2->hours
				|| ff1->minutes != ff2->minutes)
				return false;
		}
		else if((*f1)->IsLadder())
		{
			if(!(*f2)->IsLadder())
				return false;
			PlayerItemEffectLadder* ff1 = (PlayerItemEffectLadder*)(*f1), 
				* ff2 = (PlayerItemEffectLadder*)(*f2);
			if(ff1->monsterCount != ff2->monsterCount)
				return false;
		}
		else if((*f1)->IsMinMax())
		{
			if(!(*f2)->IsMinMax())
				return false;
			PlayerItemEffectMinMax* ff1 = (PlayerItemEffectMinMax*)(*f1), 
				* ff2 = (PlayerItemEffectMinMax*)(*f2);
			if(ff1->min != ff2->min || ff1->max != ff2->max)
				return false;
		}
		else if((*f1)->IsMount())
		{
			if(!(*f2)->IsMount())
				return false;
			PlayerItemEffectMount* ff1 = (PlayerItemEffectMount*)(*f1), 
				* ff2 = (PlayerItemEffectMount*)(*f2);
			if(ff1->mountId != ff2->mountId || ff1->date != ff2->date
				|| ff1->modelId != ff2->modelId)
				return false;
		}
		else if((*f1)->IsString())
		{
			if(!(*f2)->IsString())
				return false;
			PlayerItemEffectString* ff1 = (PlayerItemEffectString*)(*f1), 
				* ff2 = (PlayerItemEffectString*)(*f2);
			if(ff1->value != ff2->value)
				return false;
		}
	}
	return true;
}

void PlayerItem::DeleteEffect(int16 actionId)
{
	for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
	{
		if((*it)->actionId == actionId)
		{
			delete *it;
			m_effects.erase(it);
			return;
		}
	}
}

PlayerItem::~PlayerItem()
{
	for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
		delete *it;
}

PlayerItemEffect* PlayerItem::GetEffect(int16 actionId)
{
	for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
		if((*it)->actionId == actionId)
			return *it;
	return NULL;
}

std::string PlayerItem::StatsToString()
{
	std::ostringstream str;
	for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
	{
		if(it != m_effects.begin())
			str<<";";

		switch((*it)->ToObjectEffect()->GetProtocol())
		{
		case OBJECT_EFFECT_STRING:
			{
				PlayerItemEffectString* effect = (PlayerItemEffectString*)(*it);
				str<<OBJECT_EFFECT_STRING<<","<<effect->actionId<<","<<effect->value;
			}
			break;
		case OBJECT_EFFECT_MOUNT:
			{
				PlayerItemEffectMount* effect = (PlayerItemEffectMount*)(*it);
				str<<OBJECT_EFFECT_MOUNT<<","<<effect->actionId<<","<<effect->mountId<<","<<effect->date;
				str<<","<<effect->modelId;
			}
			break;
		case OBJECT_EFFECT_MIN_MAX:
			{
				PlayerItemEffectMinMax* effect = (PlayerItemEffectMinMax*)(*it);
				str<<OBJECT_EFFECT_MIN_MAX<<","<<effect->actionId<<","<<effect->min<<","<<effect->max;
			}
			break;
		case OBJECT_EFFECT_LADDER:
			{
				PlayerItemEffectLadder* effect = (PlayerItemEffectLadder*)(*it);
				str<<OBJECT_EFFECT_LADDER<<","<<effect->actionId<<","<<effect->monsterCount;
			}
			break;
		case OBJECT_EFFECT_DURATION:
			{
				PlayerItemEffectDuration* effect = (PlayerItemEffectDuration*)(*it);
				str<<OBJECT_EFFECT_DURATION<<","<<effect->actionId<<","<<effect->days<<","<<effect->hours;
				str<<","<<effect->minutes;
			}
			break;
		case OBJECT_EFFECT_DATE:
			{
				PlayerItemEffectDate* effect = (PlayerItemEffectDate*)(*it);
				str<<OBJECT_EFFECT_DATE<<","<<effect->actionId<<","<<effect->year<<","<<effect->month;
				str<<","<<effect->day<<","<<effect->hour<<","<<effect->minute;
			}
			break;
		case OBJECT_EFFECT_CREATURE:
			{
				PlayerItemEffectCreature* effect = (PlayerItemEffectCreature*)(*it);
				str<<OBJECT_EFFECT_CREATURE<<","<<effect->actionId<<","<<effect->monsterFamilyId;
			}
			break;
		case OBJECT_EFFECT_DICE:
			{
				PlayerItemEffectDice* effect = (PlayerItemEffectDice*)(*it);
				str<<OBJECT_EFFECT_DICE<<","<<effect->actionId<<","<<effect->diceNum<<","<<effect->diceSide<<","<<effect->diceConst;
			}
			break;
		case OBJECT_EFFECT_INTEGER:
			{
				PlayerItemEffectInteger* effect = (PlayerItemEffectInteger*)(*it);
				str<<OBJECT_EFFECT_INTEGER<<","<<effect->actionId<<","<<effect->value;
			}
			break;
		case OBJECT_EFFECT:
			{
				PlayerItemEffect* effect = (PlayerItemEffect*)(*it);
				str<<OBJECT_EFFECT<<","<<effect->actionId;
			}
			break;
		}
	}
	return str.str();
}

void PlayerItem::Save()
{
	Desperion::sDatabase.Execute("UPDATE character_items SET quantity=%u, pos=%u, stats='%s', owner=%u WHERE guid=%u LIMIT 1;",
		m_quantity, m_pos, StatsToString().c_str(), m_owner ? m_owner->GetGuid() : -1, m_guid);
}

void PlayerItem::DeleteFromDB(int guid)
{
	Desperion::sDatabase.Execute("DELETE FROM character_items WHERE guid=%u LIMIT 1;", guid);
}