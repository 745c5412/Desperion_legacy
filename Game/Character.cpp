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

PlayerItem* Character::GetItem(int guid)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetGuid() == guid)
			return *it;
	return NULL;
}

bool Character::HasEquiped(int16 id)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetPos() != INVENTORY_POSITION_NOT_EQUIPED && (*it)->GetItem()->GetId() == id)
			return true;
	return false;
}

PlayerItem* Character::GetItemByPos(uint8 pos)
{
	if(pos == INVENTORY_POSITION_NOT_EQUIPED)
		return NULL;
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetPos() == pos)
			return *it;
	return NULL;
}

void Character::DeleteItem(int guid, bool dealloc, bool db)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		if((*it)->GetGuid() == guid)
		{
			if(dealloc)
				delete *it;
			if(db)
				PlayerItem::DeleteFromDB(guid);
			m_items.erase(it);
			return;
		}
	}
}

void Character::AddItem(PlayerItem* item)
{
	m_items.push_back(item);
}

PlayerItem* Character::GetSimilarItem(PlayerItem* i)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		PlayerItem* i2 = *it;
		if(i2->GetItem()->GetId() == i->GetItem()->GetId()
			&& i->GetGuid() != i2->GetGuid() && i2->GetPos() == INVENTORY_POSITION_NOT_EQUIPED
			&& false) // sameStats
			return i2;
	}
	return NULL;
}

void Character::MoveItem(PlayerItem* item, uint8 pos, bool create)
{
	PlayerItem* item2;
	if((item2 = GetSimilarItem(item)) != NULL)
	{
		item2->SetQuantity(item2->GetQuantity() + item->GetQuantity());
		m_session->Send(ObjectQuantityMessage(item2->GetGuid(), item2->GetQuantity()));

		if(!create)
			m_session->Send(ObjectDeletedMessage(item->GetGuid()));
		DeleteItem(item->GetGuid(), true, true);
	}
	else
	{
		if(item->GetQuantity() > 1 && !create)
		{
			PlayerItem* newItem = new PlayerItem;
			newItem->Init(PlayerItem::GetNextItemGuid(), item->GetItem(), 1, INVENTORY_POSITION_NOT_EQUIPED, item->GetEffects(), this);
			item->SetQuantity(item->GetQuantity() - 1);
			AddItem(newItem);
			newItem->SetPos(pos);
			PlayerItem::InsertIntoDB(newItem);

			m_session->Send(ObjectAddedMessage(ObjectItem(newItem)));
			m_session->Send(ObjectQuantityMessage(item->GetGuid(), item->GetQuantity()));
		}
		else
		{
			if(!create)
			{
				item->SetPos(pos);
				m_session->Send(ObjectMovementMessage(item->GetGuid(), item->GetPos()));
			}
			else
				m_session->Send(ObjectAddedMessage(ObjectItem(item)));
		}
	}
}

void Character::MoveItemFromMap(PlayerItem* item)
{
	PlayerItem* item2;
	if((item2 = GetSimilarItem(item)) != NULL)
	{
		item2->SetQuantity(item2->GetQuantity() + item->GetQuantity());
		PlayerItem::DeleteFromDB(item->GetGuid());
		delete item;

		m_session->Send(ObjectQuantityMessage(item2->GetGuid(), item2->GetQuantity()));
	}
	else
	{
		item->SetOwner(this);
		AddItem(item);

		m_session->Send(ObjectAddedMessage(ObjectItem(item)));
		item->Save();
	}
}

void Character::Save()
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		(*it)->Save();

	std::ostringstream zaaps;
	for(size_t a = 0; a < m_zaaps.size(); ++a)
	{
		if(a != 0)
			zaaps<<",";
		zaaps<<m_zaaps.at(a);
	}

	std::ostringstream emotes;
	for(size_t a = 0; a < m_emotes.size(); ++a)
	{
		if(a != 0)
			emotes<<",";
		emotes<<uint16(m_emotes.at(a));
	}
	Desperion::sDatabase->Execute("UPDATE characters SET zaaps='%s', currentMap=%u, currentCell=%u, spells='%s', saveMap=%u, \
								  saveCell=%u, jobs='%s', mountXp=%u, mountId=%d, isDead=%u, title=%u, isMerchant=%u, emotes='%s' \
								  WHERE guid=%u LIMIT 1;", zaaps.str().c_str(), m_map->GetId(), m_cell, "", m_saveMap, m_saveCell,
								  "", m_mountXp, -1, 0, m_title, 0, emotes.str().c_str(), m_guid);
	Desperion::sDatabase->Execute("UPDATE character_minimals SET level=%u, name='%s', entityLook='%s', breed=%u, sex=%u \
								  WHERE id=%u LIMIT 1;", m_level, m_name.c_str(), Desperion::BufferToDb(m_look.Serialize(-1)).c_str(), m_breed, 
								  m_sex ? 1 : 0, m_guid);
}

Character::~Character()
{
	CharacterMinimals* ch = World::Instance().GetCharacterMinimals(m_guid);
	if(ch != NULL)
		ch->onlineCharacter = NULL;
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		delete *it;
	m_items.clear();
}

void Character::Init(Field* fields, CharacterMinimals* ch, Session* session)
{
	int mapId = fields[2].GetInt32();
	Map* map = World::Instance().GetMap(mapId);
	if(map == NULL)
	{
		std::ostringstream str;
		str<<"Map "<<mapId<<" doesn't exist!";
		throw ServerError(str.str().c_str());
	}
	DisplayableEntity::Init(fields[0].GetInt32(), ch->look, fields[3].GetInt16(), World::Instance().GetMap(fields[2].GetInt32()), 
		DIRECTION_SOUTH_WEST);
	NamedEntity::Init(ch->name);
	HumanEntity::Init(0, 0, fields[11].GetInt16(), "");

	std::string zaaps = fields[1].GetString();
	{
		ByteBuffer buffer = Desperion::DbToBuffer(zaaps);
		uint16 size;
		buffer>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int zaap;
			buffer>>zaap;
			m_zaaps.push_back(zaap);
		}
	}
	//spells
	m_saveMap = fields[5].GetInt32();
	m_saveCell = fields[6].GetInt16();
	//jobs
	m_mountXp = fields[8].GetInt8();
	//mount
	m_isDead = fields[10].GetBool();
	m_isMerchant = fields[12].GetBool();
	std::string emotes = fields[13].GetString();
	{
		ByteBuffer buffer = Desperion::DbToBuffer(emotes);
		uint16 size;
		buffer>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 emote;
			buffer>>emote;
			m_emotes.push_back(emote);
		}
	}

	m_level = ch->level;
	m_breed = ch->breed;
	m_sex = ch->sex;
	m_account = ch->account;
	m_session = session;
	m_context = ROLE_PLAY;
	m_nextCell = -1;
	m_nextDirection = -1;
	ch->onlineCharacter = this;
	InitItems();
	m_stats.Init(fields, m_level);
	ApplyEffect(&StatsRow::base, 125, fields[25].GetInt16());
	ApplyEffect(&StatsRow::base, 124, fields[26].GetInt16());
	ApplyEffect(&StatsRow::base, 118, fields[27].GetInt16());
	ApplyEffect(&StatsRow::base, 126, fields[28].GetInt16());
	ApplyEffect(&StatsRow::base, 123, fields[29].GetInt16());
	ApplyEffect(&StatsRow::base, 119, fields[30].GetInt16());
}

void Character::InitItems()
{
	QueryResult* QR = Desperion::sDatabase->Query("SELECT * FROM character_items WHERE owner=%u;", m_guid);
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		PlayerItem* it = new PlayerItem;
		it->Init(fields);
		m_items.push_back(it);
	}while(QR->NextRow());
	delete QR;
}

bool Character::ApplyEffect(double StatsRow::*stat, int id, int val)
{
	EffectInstanceInteger e;
	e.value = val;
	e.effectId = id;
	return ApplyEffect(stat, e);
}

bool Character::ApplyEffect(double StatsRow::*stat, EffectInstanceInteger& e)
{
	double v = e.value;
	switch(e.effectId)
	{
	case 1076:
		m_stats.neutralElementResistPercent.*stat += v;
		m_stats.fireElementResistPercent.*stat += v;
		m_stats.waterElementResistPercent.*stat += v;
		m_stats.airElementResistPercent.*stat += v;
		m_stats.earthElementResistPercent.*stat += v;
		break;
	case 1077:
		m_stats.neutralElementResistPercent.*stat -= v;
		m_stats.fireElementResistPercent.*stat -= v;
		m_stats.waterElementResistPercent.*stat -= v;
		m_stats.airElementResistPercent.*stat -= v;
		m_stats.earthElementResistPercent.*stat -= v;
		break;
	case 124:
		m_stats.wisdom.*stat += v;
		m_stats.dodgePALostProbability.*stat += v/10;
		m_stats.dodgePMLostProbability.*stat += v/10;
		m_stats.PAAttack.*stat += v/10;
		m_stats.PMAttack.*stat += v/10;
		break;
	case 156:
		m_stats.wisdom.*stat -= v;
		m_stats.dodgePALostProbability.*stat -= v/10;
		m_stats.dodgePMLostProbability.*stat -= v/10;
		m_stats.PAAttack.*stat -= v/10;
		m_stats.PMAttack.*stat -= v/10;
		break;
	case 126:
		m_stats.intelligence.*stat += v;
		m_stats.healBonus.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 155:
		m_stats.intelligence.*stat -= v;
		m_stats.healBonus.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 119:
		m_stats.agility.*stat += v;
		m_stats.tackleBlock.*stat += v/10;
		m_stats.tackleEvade.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 154:
		m_stats.agility.*stat -= v;
		m_stats.tackleBlock.*stat -= v/10;
		m_stats.tackleEvade.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 123:
		m_stats.chance.*stat += v;
		m_stats.prospecting.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 152:
		m_stats.chance.*stat -= v;
		m_stats.prospecting.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 125:
		m_stats.vitality.*stat += v;
		break;
	case 153:
		m_stats.vitality.*stat -= v;
		break;
	case 118:
		m_stats.strength.*stat += v;
		m_stats.initiative.*stat += v;
		break;
	case 157:
		m_stats.strength.*stat -= v;
		m_stats.initiative.*stat -= v;
		break;
	default:
		return false;
	}
	return true;
}