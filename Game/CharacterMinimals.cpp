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

void DSubEntity::Init(ByteBuffer& buffer)
{
	buffer>>bindingPointCategory>>bindingPointIndex;
	subEntityLook = new DEntityLook;
	subEntityLook->Init(buffer);
}

ByteBuffer DSubEntity::Serialize() const
{
	ByteBuffer buffer;
	buffer<<bindingPointCategory<<bindingPointIndex;
	buffer<<subEntityLook->Serialize(-1);

	return buffer;
}

DSubEntity::~DSubEntity()
{
	delete subEntityLook;
}

ByteBuffer CharacterMinimals::Serialize() const
{
	ByteBuffer buffer;
	buffer<<id<<level<<name;
	buffer<<look.Serialize(id);
	buffer<<breed<<sex;

	return buffer;
}

ByteBuffer DEntityLook::Serialize(int guid) const
{
	std::vector<int16> items;
	if(guid != -1)
	{
		QueryResult* QR = Desperion::sDatabase->Query("SELECT * FROM character_items WHERE (pos=%d OR pos=%d OR pos=%d OR pos=%d OR pos=%d) AND owner=%u;",
			ACCESSORY_POSITION_CAPE, ACCESSORY_POSITION_HAT, ACCESSORY_POSITION_WEAPON, ACCESSORY_POSITION_PETS, ACCESSORY_POSITION_SHIELD,
			guid);
		if(QR)
		{
			do
			{
				Field* fields = QR->Fetch();
				PlayerItem item;
				item.Init(fields);
				items.push_back(item.GetItem()->GetAppearanceId());
			}while(QR->NextRow());
		}
		delete QR;
	}
	return Serialize(items);
}

ByteBuffer DEntityLook::Serialize(Character* ch) const
{
	const std::list<PlayerItem*>& list = ch->GetItems();
	std::vector<int16> items;
	for(std::list<PlayerItem*>::const_iterator it = list.begin(); it != list.end(); ++it)
		items.push_back((*it)->GetItem()->GetAppearanceId());
	return Serialize(items);
}

ByteBuffer DEntityLook::Serialize(const std::vector<int16>& items) const
{
	ByteBuffer buffer;
	buffer<<bonesId;

	uint16 skinsSize = skins.size();
	uint16 itemsSize = items.size();
	buffer<<uint16(skinsSize + itemsSize);
	for(uint16 a = 0; a < skinsSize; ++a)
		buffer<<skins[a];
	for(uint16 a = 0; a < itemsSize; ++a)
		buffer<<items[a];

	uint16 colorsSize = indexedColors.size();
	buffer<<colorsSize;
	for(uint16 a = 0; a < colorsSize; ++a)
		buffer<<indexedColors[a];

	uint16 scalesSize = scales.size();
	buffer<<scalesSize;
	for(uint16 a = 0; a < scalesSize; ++a)
		buffer<<scales[a];

	uint16 subSize = subentities.size();
	buffer<<subSize;
	for(uint16 a = 0; a < subSize; ++a)
		buffer<<subentities[a].Serialize();

	return buffer;
}