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
	MapInformationsRequestMessage data;
	data.Deserialize(packet);

	Map* map = m_char->GetMap();

	Send(MapComplementaryInformationsDataMessage(map->GetSubareaId(), map->GetId(), 0, map->GetActors()));
	const std::tr1::unordered_map<int16, PlayerItem*>& items = map->GetItems();
	if(items.empty())
		return;
	std::vector<int16> cells;
	std::vector<int> ids;
	for(std::tr1::unordered_map<int16, PlayerItem*>::const_iterator it = items.begin(); it != items.end(); ++it)
	{
		cells.push_back(it->first);
		ids.push_back(it->second->GetItem()->GetId());
	}
	Send(ObjectGroundListAddedMessage(cells, ids));
}

void Session::HandleGameContextCreateRequestMessage(ByteBuffer& packet)
{
	GameContextCreateRequestMessage data;
	data.Deserialize(packet);

	Send(GameContextDestroyMessage());
	Send(GameContextCreateMessage(m_char->GetContextType()));
	
	Send(CurrentMapMessage(m_char->GetMap()->GetId()));
	Send(TextInformationMessage(1, 89, std::vector<std::string>()));
}

void Session::HandleChangeMapMessage(ByteBuffer& packet)
{
	ChangeMapMessage data;
	data.Deserialize(packet);

	Map* newMap = World::Instance().GetMap(data.mapId);

	if(m_char->GetNextCell() != -1)
		return;
	if(newMap == NULL)
		return;

	int16 newCell = m_char->GetCell();
	if(newMap->GetId() == m_char->GetMap()->GetTopMap())
		newCell += 532;
	else if(newMap->GetId() == m_char->GetMap()->GetBottomMap())
		newCell -= 532;
	else if(newMap->GetId() == m_char->GetMap()->GetLeftMap())
		newCell += 13;
	else if(newMap->GetId() == m_char->GetMap()->GetRightMap())
		newCell -= 13;
	else
		return;

	m_char->GetMap()->RemoveActor(m_char->GetGuid());
	m_char->SetMap(newMap);
	m_char->SetCell(newCell);
	newMap->AddActor(m_char);
	Send(CurrentMapMessage(m_char->GetMap()->GetId()));
}

void Session::HandleGameMapMovementConfirmMessage(ByteBuffer& packet)
{
	GameMapMovementConfirmMessage data;
	data.Deserialize(packet);

	if(m_char->GetNextCell() == -1)
		return;

	// todo: timer de vérification
	m_char->SetCell(m_char->GetNextCell());
	m_char->SetDirection(m_char->GetNextDirection());
	m_char->SetNextCell(-1);
	m_char->SetNextDirection(-1);

	PlayerItem* i = m_char->GetMap()->GetItem(m_char->GetCell());
	if(i != NULL)
	{
		m_char->GetMap()->Send(ObjectGroundRemovedMessage(m_char->GetCell()));
		m_char->GetMap()->DeleteItem(m_char->GetCell());
		m_char->MoveItemFromMap(i);
	}
	Send(BasicNoOperationMessage());
}

void Session::HandleGameMapMovementRequestMessage(ByteBuffer& packet)
{
	GameMapMovementRequestMessage data;
	data.Deserialize(packet);
	
	if(data.keyMovements.empty())
		return;

	// todo: pathfinding
	size_t size = data.keyMovements.size();
	m_char->SetNextCell(data.keyMovements[size - 1] & 4095);
	m_char->SetNextDirection((m_char->GetNextCell() ^ data.keyMovements[size - 1]) >> 12);
	m_char->GetMap()->Send(GameMapMovementMessage(data.keyMovements, m_char->GetGuid()));
}