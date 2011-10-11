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
	m_posX = fields[1].GetInt16();
	m_posY = fields[2].GetInt16();
	m_capabilities = fields[4].GetInt32();
	m_subareaId = fields[7].GetInt16();
}

void Map::AddActor(DisplayableEntity* actor)
{
	m_actors.push_back(actor);
}

void Map::RemoveActor(int guid)
{
	for(std::list<DisplayableEntity*>::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
	{
		if((*it)->GetGuid() == guid)
		{
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