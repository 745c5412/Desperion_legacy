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
	MapInformationsRequestMessage data(packet);

	Map* map = m_char->GetMap();
	Send(MapComplementaryInformationsDataMessage(map->GetSubareaId(), map->GetId(), 0, map->GetActors()));
}

void Session::HandleGameContextCreateRequestMessage(ByteBuffer& packet)
{
	GameContextCreateRequestMessage data(packet);

	Send(GameContextDestroyMessage());
	Send(GameContextCreateMessage(m_char->GetContextType()));
	Send(InventoryContentMessage(m_char->GetItems(), m_char->GetStats().GetKamas()));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
	Send(CharacterStatsListMessage(m_char));
	
	//spellList
	//shortCuts
	
	Send(CurrentMapMessage(m_char->GetMap()->GetId()));
	Send(TextInformationMessage(1, 89, std::vector<std::string>()));
}

void Session::HandleChangeMapMessage(ByteBuffer& packet)
{
	ChangeMapMessage data(packet);

	Map* newMap = World::Instance().GetMap(data.mapId);

	if(m_char->GetNextCell() != -1)
		return;
	if(newMap == NULL)
		return;

	m_char->GetMap()->RemoveActor(m_char->GetGuid());
	newMap->AddActor(m_char);
	m_char->SetMap(newMap);
	m_char->SetCell(211); // todo: en fonction de haut, bas, droite, gauche
	Send(CurrentMapMessage(m_char->GetMap()->GetId()));
}

void Session::HandleGameMapMovementConfirmMessage(ByteBuffer& packet)
{
	GameMapMovementConfirmMessage data(packet);

	if(m_char->GetNextCell() == -1)
		return;

	// todo: timer de vérification
	m_char->SetCell(m_char->GetNextCell());
	m_char->SetNextCell(-1);

	Send(BasicNoOperationMessage());
}

void Session::HandleGameMapMovementRequestMessage(ByteBuffer& packet)
{
	GameMapMovementRequestMessage data(packet);

	// todo: pathfinding
	m_char->SetNextCell(data.keyMovements[data.keyMovements.size() - 1] & 0xff);
	SendToMap(GameMapMovementMessage(data.keyMovements, m_char->GetGuid()), true);
}