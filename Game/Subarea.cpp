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

void SubArea::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	m_areaId = fields[1].GetInt32();
	Desperion::FastSplit<';'>(m_spawns, std::string(fields[2].GetString()), S, true);
}

void SubArea::Send(DofusMessage& message)
{
	for(std::list<Map*>::iterator it = m_maps.begin(); it != m_maps.end(); ++it)
		(*it)->Send(message);
}