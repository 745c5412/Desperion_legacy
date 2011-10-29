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

	// TODO: ApplyEffect
	if(m_pos == INVENTORY_POSITION_NOT_EQUIPED && pos != INVENTORY_POSITION_NOT_EQUIPED && m_owner)
	{
		for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			m_owner->ApplyEffect(&StatsRow::objects, (*it)->actionId, ((PlayerItemEffectInteger*)*it)->value);
	}
	if(m_pos != INVENTORY_POSITION_NOT_EQUIPED && pos == INVENTORY_POSITION_NOT_EQUIPED && m_owner)
	{
		for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			m_owner->ApplyEffect(&StatsRow::objects, (*it)->actionId, -((PlayerItemEffectInteger*)*it)->value);
	}

	m_pos = pos;
}

int PlayerItem::GetNextItemGuid()
{
	int guid = 1;
	m_guidLock.lock();
	QueryResult* QR = Desperion::sDatabase->Query("SELECT guid FROM character_items ORDER BY guid DESC;");
	if(QR)
		guid = (QR->Fetch()[0].GetInt32()) + 1;
	delete QR;
	m_guidLock.unlock();
	return guid;
}

void PlayerItem::InsertIntoDB(PlayerItem* item)
{
	Desperion::sDatabase->Execute("INSERT INTO character_items VALUES(%u, %u, %u, %u, '%s', %u);", item->GetGuid(),
		item->GetItem()->GetId(), item->GetQuantity(), item->GetPos(), item->StatsToString().c_str(), 
		item->GetOwner() ? item->GetOwner()->GetGuid() : 0);
}

PlayerItem::~PlayerItem()
{
	for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
		delete *it;
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
	Desperion::sDatabase->Execute("UPDATE character_items SET quantity=%u, pos=%u, stats='%s', owner=%u WHERE guid=%u LIMIT 1;",
		m_quantity, m_pos, StatsToString().c_str(), m_owner ? m_owner->GetGuid() : -1, m_guid);
}

void PlayerItem::DeleteFromDB(int guid)
{
	Desperion::sDatabase->Execute("DELETE FROM character_items WHERE guid=%u LIMIT 1;", guid);
}