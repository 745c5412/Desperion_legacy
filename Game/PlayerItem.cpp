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
			m_owner->ApplyEffect(&StatsRow::objects, *it, true);
	}
	else if(m_pos != INVENTORY_POSITION_NOT_EQUIPED && pos == INVENTORY_POSITION_NOT_EQUIPED && m_owner)
	{
		for(std::vector<PlayerItemEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			m_owner->ApplyEffect(&StatsRow::objects, *it, false);
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

void PlayerItem::InsertIntoDB(PlayerItem* item)
{
	Desperion::sDatabase->AsyncExecute("INSERT INTO \"character_items\" VALUES(%u, %u, %u, %u, '%s', %u);", item->GetGuid(),
		item->GetItem()->GetId(), item->GetQuantity(), item->GetPos(), item->StatsToString().c_str(), 
		item->GetOwner() ? item->GetOwner()->GetGuid() : 0);
}

bool PlayerItem::SameStats(const PlayerItem* i1, const PlayerItem* i2)
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
		if(!(*f1)->Compare(*f2))
			return false;
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

std::string PlayerItem::StatsToString() const
{
	std::ostringstream str;
	for(std::vector<PlayerItemEffect*>::const_iterator it = m_effects.begin(); it != m_effects.end(); ++it)
	{
		if(it != m_effects.begin())
			str<<";";
		(*it)->ToString(str);
	}
	return str.str();
}

void PlayerItem::Save(std::vector<boost::shared_array<const char> >& queries) const
{
	queries.push_back(Desperion::FormatString("UPDATE \"character_items\" SET \"quantity\"=%u, \"pos\"=%u, \"stats\"='%s', \"owner\"=%u WHERE \"guid\"=%u;",
		m_quantity, m_pos, StatsToString().c_str(), m_owner ? m_owner->GetGuid() : -1, m_guid));
}

void PlayerItem::DeleteFromDB(int guid)
{
	Desperion::sDatabase->AsyncExecute("DELETE FROM \"character_items\" WHERE \"guid\"=%u;", guid);
}