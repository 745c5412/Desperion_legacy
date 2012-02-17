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

void Map::Init(Field* fields)
{
	m_id = fields[0].GetInt32();
	Desperion::FastSplit<','>(m_cells, std::string(fields[1].GetString()), Desperion::SplitInt);
	m_topMap = fields[2].GetInt32();
	m_bottomMap = fields[3].GetInt32();
	m_rightMap = fields[4].GetInt32();
	m_leftMap = fields[5].GetInt32();
	m_spawnSubAreaMonsters = fields[6].GetBool();
	m_posX = fields[7].GetInt16();
	m_posY = fields[8].GetInt16();
	m_capabilities = fields[9].GetInt32();
	m_subareaId = fields[10].GetInt16();
}

DisplayableEntity* Map::GetEntityOnCell(int16 cell)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
		if((*it)->GetCell() == cell)
			return *it;
	return NULL;
}

void MonsterGroup::Init(int id, int16 cell, MonsterGrade* mainMonster, std::vector<MonsterGrade*>& monsters, Map* map, int8 dir)
{
	DisplayableEntity::Init(id, World::Instance().GetMonster(mainMonster->monsterId)->GetLook(), cell, map, dir);
	this->monsters = monsters;
	this->mainMonster = mainMonster;
	spawnDate = time(NULL);
}

int16 MonsterGroup::GetAgeBonus() const
{
	int16 bonus = (time(NULL) - spawnDate) / 864;
	if(bonus > 1000 || bonus < 0) // < 0 ==> overflow
		bonus = 1000;
	return bonus;
}

GameRolePlayActorInformations* MonsterGroup::ToActor()
{
	std::vector<MonsterInGroupInformationsPtr> list;
	for(size_t a = 0; a < monsters.size(); ++a)
	{
		list.push_back(MonsterInGroupInformationsPtr(new MonsterInGroupInformations(monsters[a]->monsterId,
			monsters[a]->grade, new EntityLook(World::Instance().GetMonster(monsters[a]->monsterId)->GetLook(),
			std::vector<SubEntityPtr>()))));
	}
	return new GameRolePlayGroupMonsterInformations(m_guid, GetLook(), new EntityDispositionInformations(m_cell, m_direction),
		mainMonster->monsterId, mainMonster->grade, list, GetAgeBonus(), 0, false);
}

void Map::SpawnMonsters(SubArea* sub, time_t now)
{
	std::vector<MonsterSpawnInformations> possibleSpawns = sub->GetPossibleSpawns();
	size_t size = possibleSpawns.size();
	uint8 a = 0;
	while(a < 3)
	{
		MonsterSpawnInformations mainInfos;
		Monster* main = NULL;
		while(true)
		{
			mainInfos = possibleSpawns[RandomUInt(0, size - 1)];
			main = World::Instance().GetMonster(mainInfos.monsterId);
			if((mainInfos.maxPerZone == 0 || sub->GetMonsterCount(mainInfos.monsterId) < mainInfos.maxPerZone)
				&& RandomDouble() <= mainInfos.spawnProbability
				&& now >= main->GetMinRespawnTime() + sub->GetMonsterSpawnDate((mainInfos.monsterId)))
				break;
		}
		sub->IncMonsterCount(mainInfos.monsterId);
		sub->SetMonsterSpawnDate(mainInfos.monsterId, now);
		MonsterGroup* g = new MonsterGroup;
		int16 index = 0;
		while(index == 0)
		{
			index = RandomUInt(0, 559);
			Cell c = GetCell(index);
			if(c.id == -1 || (c.losmov & 1) != 1)
				index = 0;
		}
		std::vector<MonsterGrade*> monsters;
		uint8 groupSize = 0;
		switch(a)
		{
		case 0:
			groupSize = RandomUInt(0, 2);
			break;
		case 1:
			groupSize = RandomUInt(2, 4);
			break;
		case 2:
			groupSize = RandomUInt(4, 7);
			break;
		}
		uint8 b = 0;
		while(b < groupSize)
		{
			MonsterSpawnInformations infos = possibleSpawns[RandomUInt(0, size - 1)];
			Monster* m = World::Instance().GetMonster(infos.monsterId);
			if(infos.maxPerZone != 0 && sub->GetMonsterCount(infos.monsterId) >= infos.maxPerZone)
				continue;
			else if(RandomDouble() > infos.spawnProbability)
				continue;
			else if(now < m->GetMinRespawnTime() + sub->GetMonsterSpawnDate((infos.monsterId)))
				continue;
			monsters.push_back(m->GetMonsterGrade(RandomUInt(1, m->GetGradesSize())));
			sub->IncMonsterCount(infos.monsterId);
			sub->SetMonsterSpawnDate(infos.monsterId, now);
			++b;
		}
		g->Init(GetNextActorId(), index, main->GetMonsterGrade(RandomUInt(1, main->GetGradesSize())),
			monsters, this, 0);
		m_actors.push_back(g);
		++a;
	}
}

Map::~Map()
{
	for(std::tr1::unordered_map<int16, PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		delete it->second;
	m_items.clear();
}

PlayerItem* Map::GetItem(int16 cell)
{
	std::unordered_map<int16, PlayerItem*>::iterator it = m_items.find(cell);
	if(it != m_items.end())
		return it->second;
	return NULL;
}

void Map::AddItem(PlayerItem* item, int16 cell)
{
	m_items[cell] = item;
}

void Map::DeleteItem(int16 cell)
{
	std::unordered_map<int16, PlayerItem*>::iterator it = m_items.find(cell);
	if(it != m_items.end())
		m_items.erase(it);
}

void Map::AddActor(DisplayableEntity* actor)
{
	m_actors.push_back(actor);
	Send(GameRolePlayShowActorMessage(actor->ToActor()), actor->GetGuid());
}

void Map::Send(const DofusMessage& data, int guid)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
	{
		if(!(*it)->IsCharacter())
			continue;
		Character* ch = ToCharacter(*it);
		if(ch->GetGuid() == guid)
			continue;
		ch->GetSession()->Send(data);
	}
}

Cell Map::GetCell(uint16 index) const
{
	Cell c;
	int number = 0;
	try
	{
		number = m_cells.at(index);
		c.id = index;
	}catch(const std::out_of_range&)
	{ 
		Log::Instance().OutError("Invalid cell %u", index);
		c.id = -1; 
	}
	uint8* bytes = (uint8*)&number;
	if(ByteBuffer::ENDIANNESS == BIG_ENDIAN)
		SwapBytes(bytes, sizeof(int));
	c.losmov = bytes[0];
	c.speed = bytes[1];
	return c;
}

void Map::RemoveActor(int guid)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
	{
		if((*it)->GetGuid() == guid)
		{
			Send(GameContextRemoveElementMessage(guid), guid);
			m_actors.erase(it);
			return;
		}
	}
}

DisplayableEntity* Map::GetActor(int guid)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
		if((*it)->GetGuid() == guid)
			return *it;
	return NULL;
}