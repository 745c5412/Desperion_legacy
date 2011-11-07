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
	std::vector<int16> items, bones;
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
				if(item.GetPos() != ACCESSORY_POSITION_PETS)
				{
					int appearanceId;
					PlayerItemEffectInteger* effect = (PlayerItemEffectInteger*)item.GetEffect(972);
					if(effect == NULL)
						appearanceId = item.GetItem()->GetAppearanceId();
					else
					{
						PlayerItemEffectInteger* type = (PlayerItemEffectInteger*)item.GetEffect(970);
						if(type != NULL)
							appearanceId = DofusUtils::GetObviAppearanceBySkinId(effect->value, type->value);
					}
					if(appearanceId != 0)
						items.push_back(appearanceId);
				}
				else
					bones.push_back(item.GetItem()->GetAppearanceId());
			}while(QR->NextRow());
		}
		delete QR;
	}
	return Serialize(items, bones);
}

ByteBuffer DEntityLook::Serialize(Character* ch) const
{
	const std::list<PlayerItem*>& list = ch->GetItems();
	std::vector<int16> items, bones;
	for(std::list<PlayerItem*>::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		switch((*it)->GetPos())
		{
		case ACCESSORY_POSITION_HAT:
		case ACCESSORY_POSITION_CAPE:
		case ACCESSORY_POSITION_WEAPON:
		case ACCESSORY_POSITION_SHIELD:
			{
				int appearanceId = 0;
				PlayerItemEffectInteger* effect = (PlayerItemEffectInteger*)(*it)->GetEffect(972);
				if(effect == NULL)
					appearanceId = (*it)->GetItem()->GetAppearanceId();
				else
				{
					PlayerItemEffectInteger* type = (PlayerItemEffectInteger*)(*it)->GetEffect(970);
					if(type != NULL)
						appearanceId = DofusUtils::GetObviAppearanceBySkinId(effect->value, type->value);
				}
				if(appearanceId != 0)
					items.push_back(appearanceId);
			}
			break;
		case ACCESSORY_POSITION_PETS:
			bones.push_back((*it)->GetItem()->GetAppearanceId());
			break;
		}
	}
	return Serialize(items, bones);
}

ByteBuffer DEntityLook::Serialize(const std::vector<int16>& items, const std::vector<int16>& bones) const
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
	uint16 bonesSize = bones.size();
	buffer<<uint16(subSize + bonesSize);
	for(uint16 a = 0; a < subSize; ++a)
		buffer<<subentities[a].Serialize();
	for(uint16 a = 0; a < bonesSize; ++a)
	{
		DSubEntity d;
		d.bindingPointCategory = 1;
		d.bindingPointIndex = 0;
		d.subEntityLook = new DEntityLook;
		d.subEntityLook->bonesId = bones[a];
		buffer<<d.Serialize();
	}

	return buffer;
}