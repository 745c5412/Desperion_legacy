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

void Session::HandleMapInformationsRequestMessage(ByteBuffer& packet)
{
	Packet map(SMSG_MAP_COMPLEMENTARY_INFORMATIONS_DATA);
	map<<int16(1)<<m_char->GetCurrentMap()<<int8(2)<<uint16(0); // subareaId, mapId, subareaAlignmentSide, sizeof(HouseInformations)
	map<<uint16(1); // sizeof(GameRolePlayActorInformations)
	map<<m_char->SerializeActor();
	map<<uint16(0)<<uint16(0)<<uint16(0)<<uint16(0);
	Send(map);
}

void Session::HandleGameContextCreateRequestMessage(ByteBuffer& packet)
{
	Packet destroyContext(SMSG_GAME_CONTEXT_DESTROY);
	Send(destroyContext);

	Packet createContext(SMSG_GAME_CONTEXT_CREATE);
	createContext<<m_char->GetContextType();
	Send(createContext);

	Packet inventory(SMSG_INVENTORY_CONTENT);
	const std::list<PlayerItem*>& items = m_char->GetItems();
	inventory<<uint16(items.size());
	for(std::list<PlayerItem*>::const_iterator it = items.begin(); it != items.end(); ++it)
	{
		const PlayerItem* item = *it;
		inventory<<item->GetPos()<<item->GetItem()->GetId()<<uint16(0)<<false; // 0 --> powerRate, false --> overMax
		inventory<<uint16(0); // effectSize
		inventory<<item->GetGuid()<<item->GetQuantity();
	}
	inventory<<m_char->GetStats().GetKamas();
	Send(inventory);

	Packet weight(SMSG_INVENTORY_WEIGHT);
	weight<<m_char->GetCurrentPods()<<m_char->GetMaxPods();
	Send(weight);

	/*Packet stats(SMSG_CHARACTER_STATS_LIST);
	stats<<m_char->SerializeStats();
	Send(stats);*/
	
	//spellList
	//shortCuts

	Packet map(SMSG_CURRENT_MAP);
	map<<m_char->GetCurrentMap();
	Send(map);

	Packet info(SMSG_TEXT_INFORMATION);
	info<<int8(1)<<int16(89)<<uint16(0);
	Send(info);
}