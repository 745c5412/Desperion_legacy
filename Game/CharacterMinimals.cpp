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

EntityLook* CharacterMinimals::GetLook() const
{
	EntityLook* l = new EntityLook;
	l->bonesId = look.bonesId;
	l->skins = look.skins;
	l->indexedColors = look.indexedColors;
	l->scales = look.scales;

	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM character_items WHERE (pos=%d OR pos=%d OR pos=%d OR pos=%d OR pos=%d) AND owner=%u;",
			ACCESSORY_POSITION_CAPE, ACCESSORY_POSITION_HAT, ACCESSORY_POSITION_WEAPON, ACCESSORY_POSITION_PETS, ACCESSORY_POSITION_SHIELD, id);
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
					l->skins.push_back(appearanceId);
			}
			else
			{
				EntityLook* ent = new EntityLook;
				ent->bonesId = item.GetItem()->GetAppearanceId();
				l->subentities.push_back(SubEntityPtr(new SubEntity(1, 0, ent)));
			}
		}while(QR->NextRow());
	}
	return l;
}