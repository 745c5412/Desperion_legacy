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
	m_cellsString = fields[1].GetString();
	m_topMap = fields[2].GetInt32();
	m_bottomMap = fields[3].GetInt32();
	m_rightMap = fields[4].GetInt32();
	m_leftMap = fields[5].GetInt32();
	m_posX = fields[8].GetInt16();
	m_posY = fields[9].GetInt16();
	m_capabilities = fields[11].GetInt32();
	m_subareaId = fields[14].GetInt16();
	m_isBuilt = false;
}

bool Map::EntityOnCell(int16 cell)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
		if((*it)->GetCell() == cell)
			return true;
	return false;
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
	Send(GameRolePlayShowActorMessage(actor), actor->GetGuid());
}

void Map::Send(DofusMessage& data, int guid)
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
		Log::Instance().outError("Invalid cell %u", index);
		c.id = -1; 
	}
	uint8* bytes = (uint8*)&number;
	if(ByteBuffer::ENDIANNESS == BIG_ENDIAN)
		SwapBytes(bytes, sizeof(int));
	c.losmov = bytes[0];
	c.mapChangeData = bytes[1];
	c.speed = bytes[2];
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