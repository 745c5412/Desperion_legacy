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

GameServer::GameServer()
{
}

void GameServer::Init(uint16 id, std::string ip, uint16 port, uint8 state, std::string key, uint16 limit, uint8 mlvl)
{ 
	m_id = id;
	m_ip = ip;
	m_port = port;
	m_state = state;
	m_key = key;
	m_pLimit = limit;
	m_players = 0;
	m_minLevel = mlvl;
}

uint8 GameServer::GetState(uint8 level, bool subscribe) const
{
	if(level < m_minLevel)
		return NOJOIN;
	else if(m_state == ONLINE && m_players >= m_pLimit && !subscribe)
		return FULL;
	return m_state;
}