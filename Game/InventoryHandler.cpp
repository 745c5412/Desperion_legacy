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

void Session::HandleLivingObjectChangeSkinRequestMessage(ByteBuffer& packet)
{
	LivingObjectChangeSkinRequestMessage data;
	data.Deserialize(packet);

	PlayerItem* item = m_char->GetItem(data.livingUID);
	if(item == NULL)
		return;

	PlayerItemEffectInteger* obviXp = (PlayerItemEffectInteger*)item->GetEffect(974),
		* obviSkin = (PlayerItemEffectInteger*)item->GetEffect(972);
	if(obviXp == NULL || obviSkin == NULL)
		return;
	if(data.skinId > DofusUtils::GetLevelByObviXp(obviXp->value))
		return;
	item->DeleteEffect(972);
	item->AddEffect(new PlayerItemEffectInteger(972, data.skinId));

	Send(ObjectModifiedMessage(item->ToObjectItem()));
	if(item->GetPos() != INVENTORY_POSITION_NOT_EQUIPED)
		Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
	Send(BasicNoOperationMessage());
}

void Session::HandleLivingObjectDissociateMessage(ByteBuffer& packet)
{
	LivingObjectDissociateMessage data;
	data.Deserialize(packet);

	PlayerItem* item = m_char->GetItem(data.livingUID);
	if(item == NULL)
		return;

	PlayerItemEffectInteger* obviXp = (PlayerItemEffectInteger*)item->GetEffect(974),
		* obviType = (PlayerItemEffectInteger*)item->GetEffect(973),
		* obviState = (PlayerItemEffectInteger*)item->GetEffect(971),
		* obviSkin = (PlayerItemEffectInteger*)item->GetEffect(972),
		* obviTemplate = (PlayerItemEffectInteger*)item->GetEffect(970);

		PlayerItemEffectDate* obviTime = (PlayerItemEffectDate*)item->GetEffect(808),
		* exchangeTime = (PlayerItemEffectDate*)item->GetEffect(983);

		if(obviTemplate == NULL || obviXp == NULL || obviType == NULL || obviState == NULL || obviSkin == NULL || obviTime == NULL)
			return;

		Item* temp = World::Instance().GetItem(obviTemplate->value);
		if(temp == NULL)
			return;
		PlayerItem* newItem = temp->Create(1, false, m_char);
		newItem->DeleteEffect(974);
		newItem->DeleteEffect(973);
		newItem->DeleteEffect(971);
		newItem->DeleteEffect(972);
		newItem->DeleteEffect(808);
		newItem->DeleteEffect(983);

		newItem->AddEffect(obviXp->Clone());
		newItem->AddEffect(obviTime->Clone());
		newItem->AddEffect(obviState->Clone());
		newItem->AddEffect(obviType->Clone());
		newItem->AddEffect(obviSkin->Clone());
		if(exchangeTime != NULL)
			newItem->AddEffect(exchangeTime->Clone());

		PlayerItem::InsertIntoDB(newItem);
		m_char->AddItem(newItem);
		m_char->MoveItem(newItem, INVENTORY_POSITION_NOT_EQUIPED, true);

		item->DeleteEffect(974);
		item->DeleteEffect(973);
		item->DeleteEffect(971);
		item->DeleteEffect(972);
		item->DeleteEffect(808);
		item->DeleteEffect(983);
		item->DeleteEffect(970);

		Send(ObjectModifiedMessage(item->ToObjectItem()));
		if(item->GetPos() != INVENTORY_POSITION_NOT_EQUIPED)
			Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
		Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
		Send(BasicNoOperationMessage());
}

void Session::HandleLivingObjectMessageRequestMessage(ByteBuffer& packet)
{
	LivingObjectMessageRequestMessage data;
	data.Deserialize(packet);

	PlayerItem* item = m_char->GetItem(data.livingObject);
	if(item == NULL)
		return;

	Send(LivingObjectMessageMessage(data.msgId, static_cast<int>(time(NULL)), m_char->GetName(), item->GetItem()->GetId()));
}
 
void Session::HandleObjectFeedMessage(ByteBuffer& packet)
{
	ObjectFeedMessage data;
	data.Deserialize(packet);
	
	PlayerItem* obvi = m_char->GetItem(data.objectUID),
		* food = m_char->GetItem(data.foodUID);

	if(obvi == NULL || food == NULL || food->GetPos() != INVENTORY_POSITION_NOT_EQUIPED)
		return;

	PlayerItemEffectInteger* obviItem = (PlayerItemEffectInteger*)obvi->GetEffect(970),
		* obviType = (PlayerItemEffectInteger*)obvi->GetEffect(973),
		* obviXp = (PlayerItemEffectInteger*)obvi->GetEffect(974),
		* obviState = (PlayerItemEffectInteger*)obvi->GetEffect(971);
	PlayerItemEffectDate* obviTime = (PlayerItemEffectDate*)obvi->GetEffect(808);

	if(obviItem == NULL || obviType == NULL || obviType->value != food->GetItem()->GetTypeId() || obviTime == NULL
		|| obviXp == NULL || obviState == NULL)
		return;

	int newqua = food->GetQuantity() - 1;
	int xp = food->GetItem()->GetLevel() / 2;
	int oldxp = obviXp->value;
	int state = obviState->value;

	if(!newqua)
	{
		Send(ObjectDeletedMessage(food->GetGuid()));
		m_char->DeleteItem(food->GetGuid(), true, true);
	}
	else
	{
		food->SetQuantity(newqua);
		Send(ObjectQuantityMessage(food->GetGuid(), food->GetQuantity()));
	}

	time_t t = time(NULL);

	if(state < 2)
	{
		struct tm* tm = localtime(&t);
		tm->tm_year = obviTime->year;
		tm->tm_mon = obviTime->month;
		tm->tm_mday = obviTime->day;
		tm->tm_hour = obviTime->hour;
		tm->tm_min = obviTime->minute;
		obvi->DeleteEffect(974);
		obvi->AddEffect(new PlayerItemEffectInteger(974, oldxp + xp));
		if(t - mktime(tm) < 12 * 60 * 60 || state == 0)
		{
			obvi->DeleteEffect(971);
			obvi->AddEffect(new PlayerItemEffectInteger(971, state + 1));
		}
	}

	struct tm* tm = localtime(&t);
	obvi->DeleteEffect(808);
	obvi->AddEffect(new PlayerItemEffectDate(808, tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min));
	Send(ObjectModifiedMessage(obvi->ToObjectItem()));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
	Send(BasicNoOperationMessage());
}

void Session::HandleObjectDeleteMessage(ByteBuffer& packet)
{
	ObjectDeleteMessage data;
	data.Deserialize(packet);

	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL || item->GetQuantity() < data.quantity)
	{
		Send(ObjectErrorMessage(CANNOT_DESTROY));
		return;
	}

	bool mustCheck = item->GetPos() != INVENTORY_POSITION_NOT_EQUIPED;
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

	if(mustCheck)
	{
		ConditionsParser P(m_char->GetEmotes(), m_char->GetItems(), m_char->GetName());
		DofusUtils::LoopItemConditions(P, this);
		Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
		Send(GetCharacterStatsListMessage());
	}
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}

void Session::HandleObjectDropMessage(ByteBuffer& packet)
{
	ObjectDropMessage data;
	data.Deserialize(packet);
	
	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL || item->GetQuantity() < data.quantity)
	{
		Send(ObjectErrorMessage(CANNOT_DROP));
		return;
	}
	else if(item->GetEffect(983) != NULL)
	{
		Send(ObjectErrorMessage(NOT_TRADABLE));
		return;
	}

	bool mustCheck = item->GetPos() != INVENTORY_POSITION_NOT_EQUIPED;
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
	else if(newqua == 0)
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

	if(mustCheck)
	{
		ConditionsParser P(m_char->GetEmotes(), m_char->GetItems(), m_char->GetName());
		DofusUtils::LoopItemConditions(P, this);
		Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
		Send(GetCharacterStatsListMessage());
	}
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}

void Session::HandleObjectSetPositionMessage(ByteBuffer& packet)
{
	ObjectSetPositionMessage data;
	data.Deserialize(packet);
	
	PlayerItem* item = m_char->GetItem(data.objectUID);
	if(item == NULL)
		return;
	if(data.position != INVENTORY_POSITION_NOT_EQUIPED && !DofusUtils::IsValidPlaceForItem(item->GetItem(), data.position))
		return;

	PlayerItem* exItem = m_char->GetItemByPos(data.position);
	
	if(item->GetItem()->GetTypeId() == 113)
	{
		if(exItem == NULL)
		{
			Send(TextInformationMessage(1, 161, std::vector<std::string>()));
			return;
		}

		PlayerItemEffectInteger* obviXp = (PlayerItemEffectInteger*)item->GetEffect(974),
		* obviType = (PlayerItemEffectInteger*)item->GetEffect(973),
		* obviState = (PlayerItemEffectInteger*)item->GetEffect(971),
		* obviSkin = (PlayerItemEffectInteger*)item->GetEffect(972);

		PlayerItemEffectDate* obviTime = (PlayerItemEffectDate*)item->GetEffect(808),
		* exchangeTime = (PlayerItemEffectDate*)item->GetEffect(983);

		if(exItem->GetEffect(970) != NULL)
			return;
		if(obviXp == NULL || obviType == NULL || obviState == NULL || obviSkin == NULL || obviTime == NULL)
			return;
		if(exItem->GetEffect(983) != NULL)
		{
			// TODO: message
			return;
		}

		exItem->AddEffect(new PlayerItemEffectInteger(970, item->GetItem()->GetId()));
		exItem->AddEffect(obviXp->Clone());
		exItem->AddEffect(obviTime->Clone());
		exItem->AddEffect(obviType->Clone());
		exItem->AddEffect(obviState->Clone());
		exItem->AddEffect(obviSkin->Clone());
		if(exchangeTime != NULL)
			exItem->AddEffect(exchangeTime->Clone());
		if(item->GetQuantity() == 1)
		{
			Send(ObjectDeletedMessage(item->GetGuid()));
			m_char->DeleteItem(item->GetGuid(), true, true);
		}
		else
		{
			item->SetQuantity(item->GetQuantity() - 1);
			Send(ObjectQuantityMessage(item->GetGuid(), item->GetQuantity()));
		}
		Send(ObjectModifiedMessage(exItem->ToObjectItem()));
		Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
		return;
	}

	if(exItem != NULL)
	{
		m_char->UpdateItemSet(exItem->GetItem()->GetItemSetId(), boost::bind(&Character::MoveItem, m_char, exItem,
			INVENTORY_POSITION_NOT_EQUIPED, false));
	}

	if(item->GetItem()->GetLevel() > m_char->GetLevel())
	{
		Send(ObjectErrorMessage(LEVEL_TOO_LOW));
		return;
	}

	if(data.position != INVENTORY_POSITION_NOT_EQUIPED && (item->GetItem()->GetItemSetId() != -1 || item->GetItem()->GetTypeId() == 0)
		&& m_char->HasEquiped(item->GetItem()->GetId()))
	{
		Send(ObjectErrorMessage(CANNOT_EQUIP_TWICE));
		return;
	}

	ConditionsParser P(m_char->GetEmotes(), m_char->GetItems(), m_char->GetName());
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

	m_char->UpdateItemSet(item->GetItem()->GetItemSetId(), boost::bind(&Character::MoveItem, m_char, item, data.position, false));
	DofusUtils::LoopItemConditions(P, this);

	Send(GameContextRefreshEntityLookMessage(m_char->GetGuid(), m_char->GetLook()));
	Send(GetCharacterStatsListMessage());
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
}