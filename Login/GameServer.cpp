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