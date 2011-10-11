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

void HumanEntity::Init(int8 emote, uint64 emoteStartTime, int16 title, std::string titleParams)
{
	m_emoteId = emote;
	m_emoteStartTime = emoteStartTime;
	m_title = title;
	m_titleParams = titleParams;

	for(uint8 a = 0; a < RESTRICTIONS_NUMBER; ++a)
		m_restrictions[a] = false;
}

void NamedEntity::Init(std::string name)
{
	m_name = name;
}

void DisplayableEntity::Init(int guid, DEntityLook look, int16 cell, Map* map, int8 direction)
{
	m_guid = guid;
	m_look = look;
	m_cell = cell;
	m_map = map;
	m_direction = direction;
}