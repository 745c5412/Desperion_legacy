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