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

void Session::HandleObjectDeleteMessage(ByteBuffer& packet)
{
	ObjectDeleteMessage data(packet);

	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL || item->GetQuantity() < data.quantity)
	{
		Send(ObjectErrorMessage(CANNOT_DESTROY));
		return;
	}

	int newqua = item->GetQuantity() - data.quantity;
	if(!newqua)
	{
		m_char->UpdateItemSet(item->GetItem()->GetItemSetId(), 
			boost::bind(&Character::DeleteItem, m_char, data.objectUID, false, false));
		Send(ObjectDeletedMessage(data.objectUID));
	}
	else
	{
		item->SetQuantity(newqua);
		Send(ObjectQuantityMessage(data.objectUID, newqua));
	}

	ConditionsParser P(m_char->GetItems(), m_char->GetName());
	DofusUtils::LoopItemConditions(P, this);

	Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), EntityLook(m_char->GetLook(), m_char)));
	Send(CharacterStatsListMessage(m_char));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}

void Session::HandleObjectDropMessage(ByteBuffer& packet)
{
	ObjectDropMessage data(packet);
	
	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL || item->GetQuantity() < data.quantity)
	{
		Send(ObjectErrorMessage(CANNOT_DROP));
		return;
	}
	// TODO: echangeable ou non

	int newqua = item->GetQuantity() - data.quantity;

	int16 cellID;
	for(uint8 a = 0; a < 1; ++a) // todo: getNearestFreeCell
	{
		switch(a)
		{
		case 0:
			cellID = m_char->GetCell() - 14;
			break;
		case 1:
			cellID = m_char->GetCell() - 14 + 1;
			break;
		case 2:
			cellID = m_char->GetCell() + 14 - 1;
			break;
		case 3:
			cellID = m_char->GetCell() + 14;
			break;
		}
		Cell curcell = m_char->GetMap()->GetCell(cellID);
		if(curcell.id == -1 || (curcell.losmov & 128) >> 7 == 1 ||
			m_char->GetMap()->GetItem(cellID) != NULL || m_char->GetMap()->EntityOnCell(cellID))
		{
			cellID = -1;
			continue;
		}
		break;
	}
	if(cellID == -1)
	{
		Send(ObjectErrorMessage(CANNOT_DROP_NO_PLACE));
		return;
	}
	if(!newqua)
	{
		m_char->UpdateItemSet(item->GetItem()->GetItemSetId(), 
			boost::bind(&Character::DeleteItem, m_char, data.objectUID, false, false));
		Send(ObjectDeletedMessage(data.objectUID));
	}
	else
	{
		PlayerItem* toDrop = new PlayerItem;
		toDrop->Init(PlayerItem::GetNextItemGuid(), item->GetItem(), data.quantity, -1, item->GetEffects(), NULL);
		PlayerItem::InsertIntoDB(toDrop);
		item->SetQuantity(newqua);

		Send(ObjectQuantityMessage(data.objectUID, newqua));
		item = toDrop;
	}
	item->SetOwner(NULL);
	item->SetPos(INVENTORY_POSITION_NOT_EQUIPED);
	item->Save();
	m_char->GetMap()->AddItem(item, cellID);
	m_char->GetMap()->Send(ObjectGroundAddedMessage(cellID, item->GetItem()->GetId()));

	ConditionsParser P(m_char->GetItems(), m_char->GetName());
	DofusUtils::LoopItemConditions(P, this);

	Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), EntityLook(m_char->GetLook(), m_char)));
	Send(CharacterStatsListMessage(m_char));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}

void Session::HandleObjectSetPositionMessage(ByteBuffer& packet)
{
	ObjectSetPositionMessage data(packet);
	
	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL)
		return;
	if(!DofusUtils::IsValidPlaceForItem(item->GetItem(), data.position))
		return;

	// TODO: obvi
	if(item->GetItem()->GetTypeId() == 113)
		return;

	PlayerItem* exItem = m_char->GetItemByPos(data.position);
	if(exItem != NULL)
		m_char->MoveItem(exItem, INVENTORY_POSITION_NOT_EQUIPED);

	if(item->GetItem()->GetLevel() > m_char->GetLevel())
	{
		Send(ObjectErrorMessage(LEVEL_TOO_LOW));
		return;
	}

	if(data.position != INVENTORY_POSITION_NOT_EQUIPED && (item->GetItem()->GetItemSetId() != -1 || item->GetItem()->GetTypeId()
		== 0) && m_char->HasEquiped(item->GetItem()->GetId()))
	{
		Send(ObjectErrorMessage(CANNOT_EQUIP_TWICE));
		return;
	}

	ConditionsParser P(m_char->GetItems(), m_char->GetName());
	DofusUtils::FillParser(P, this);

	if(!item->GetItem()->GetCriteria().empty() && item->GetItem()->GetCriteria() != "null" && data.position != INVENTORY_POSITION_NOT_EQUIPED)
	{
		P.SetFormula(item->GetItem()->GetCriteria());
		if(!P.Eval())
		{
			// TODO: message
			return;
		}
	}

	m_char->UpdateItemSet(item->GetItem()->GetItemSetId(), 
			boost::bind(&Character::MoveItem, m_char, item, data.position, false));
	DofusUtils::LoopItemConditions(P, this);

	Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), EntityLook(m_char->GetLook(), m_char)));
	Send(CharacterStatsListMessage(m_char));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}