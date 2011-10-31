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

namespace DofusUtils
{
	bool CheckName(std::string name)
	{
		std::string authorized = "abcdefghijklmnopqrstuvwxyz-";
		if(name.size() < 3 || name.size() > 20)
			return false;

		for(uint8 a = 0; a < name.size(); ++a)
		{
			if(Desperion::IndexOf(authorized, std::tolower(name.at(a))) == -1)
				return false;
		}

		uint8 dashes = 0;

		for(uint8 a = 0; a < name.size(); ++a)
		{
			if(name.at(a) == '-')
				dashes++;
		}
		if(dashes > 1)
			return false;

		if(name.at(0) == '-' || name.at(1) == '-')
			return false;

		if(name.at(0) != std::toupper(name.at(0)))
			return false;

		for(uint8 a = 0; a < name.size(); ++a)
		{
			if(name[a] == '-')
			{
				if(a == name.size() - 1)
					return false;
			}
			else if(name.at(a) == std::toupper(name.at(a)) && a != 0)
				if(name.at(a-1) != '-')
					return false;
		}

		std::string prohibed[] = {"XELOR", "IOP", "FECA", "ENIRIPSA", "SADIDA", "ECAFLIP", "ENUTROF", "PANDAWA", "SRAM", "CRA", "OSAMODAS", "SACRIEUR", "DROP", "MULE"};
		const uint8 proLength = 14;

		for(uint8 a = 0; a < proLength; ++a)
		{
			if(Desperion::ToUpperCase(name).find(prohibed[a]) != std::string::npos)
				return false;
		}

		const char* vowels = "aeiouy";
		int count = 0;
		for(uint16 a = 0; a < name.size(); a++)
		{
			if(Desperion::IndexOf(vowels, std::tolower(name.at(a))) != 0)
				count++;
		}
		if (count < 1)
			return false;

		count = 0;
		for(uint8 a = 0; a < name.size(); a++)
		{
			if(a < 3)
				continue;
			if(name.at(a) == name.at(a-1) && name.at(a) == name.at(a-2))
				return false;
		}

		return true;
	}

	bool IsValidPlaceForItem(const Item* item, uint8 pos)
	{
		switch(item->GetId()) // pour les obvis
		{
		case 9233:
			if(pos == ACCESSORY_POSITION_CAPE)
				return true;
			break;
		case 9234:
			if(pos == ACCESSORY_POSITION_HAT)
				return true;
			break;
		case 9255:
			if(pos == ACCESSORY_POSITION_AMULET)
				return true;
			break;
		case 9256:
			if(pos == INVENTORY_POSITION_RING_LEFT || pos == INVENTORY_POSITION_RING_RIGHT)
				return true;
			break;
		}

		/*switch(item->GetTypeId())
		{
		case INVENTORY_NECKLACE:
			if(pos == INVENTORY_POSITION_NECKLACE)
				return true;
			break;
		case INVENTORY_BOW:
		case INVENTORY_WAND:
		case INVENTORY_STICK:
		case INVENTORY_DAGGERS:
		case INVENTORY_SWORD:
		case INVENTORY_HAMMER:
		case INVENTORY_SHOVEL:
		case INVENTORY_AXE:
		//case ITEM_TYPE_OUTIL:
		//case ITEM_TYPE_PIOCHE:
		//case ITEM_TYPE_FAUX:
		case INVENTORY_SOUL_ROCK:
			if(pos == INVENTORY_POSITION_WEAPON)
				return true;
			break;
		case INVENTORY_RING:
			if(pos == INVENTORY_POSITION_RING1 || pos == INVENTORY_POSITION_RING2)
				return true;
			break;
		case INVENTORY_BELT:
			if(pos == INVENTORY_POSITION_BELT)
				return true;
			break;
		case INVENTORY_SHOES:
			if(pos == INVENTORY_POSITION_SHOES)
				return true;
			break;
		case INVENTORY_HAT:
			if(pos == INVENTORY_POSITION_HAT)
				return true;
			break;
		case INVENTORY_CLOAK:
			if(pos == INVENTORY_POSITION_CLOAK)
				return true;
			break;
		case INVENTORY_PET:
			if(pos == INVENTORY_POSITION_PET)
				return true;
			break;
		case INVENTORY_DOFUS:
			if(pos == INVENTORY_POSITION_DOFUS1 
			|| pos == INVENTORY_POSITION_DOFUS2
			|| pos == INVENTORY_POSITION_DOFUS3
			|| pos == INVENTORY_POSITION_DOFUS4
			|| pos == INVENTORY_POSITION_DOFUS5
			|| pos == INVENTORY_POSITION_DOFUS6)
				return true;
			break;
		case INVENTORY_SHIELD:
			if(pos == INVENTORY_POSITION_SHIELD)
				return true;
			break;
		}*/
		return true;
	}

	void LoopItemConditions(ConditionsParser& P, Session* S)
	{
		Character* m_char = S->GetCharacter();
		bool conds = false;
		while(!conds)
		{
			const std::list<PlayerItem*>& list = m_char->GetItems();
			FillParser(P, S, false);

			conds = true;
			for(std::list<PlayerItem*>::const_iterator it = list.begin(); it != list.end(); ++it)
			{
				PlayerItem* current = *it;
				conds = true;
				if(current->GetItem()->GetCriteria().empty() || current->GetItem()->GetCriteria() == "null")
					continue;
				if(current->GetPos() == INVENTORY_POSITION_NOT_EQUIPED)
					continue;

				P.SetFormula(current->GetItem()->GetCriteria());
				if(!P.Eval())
				{
					conds = false;
					m_char->UpdateItemSet(current->GetItem()->GetItemSetId(), 
						boost::bind(&Character::MoveItem, m_char, current, INVENTORY_POSITION_NOT_EQUIPED, false));
					break;
				}
			}
		}
	}

	void FillParser(ConditionsParser& P, Session* S, bool full)
	{
		// TODO: autres stats
		Character* m_char = S->GetCharacter();
		P.AddVar("CI", m_char->GetStats().intelligence.Total());
		P.AddVar("CV", m_char->GetStats().vitality.Total());
		P.AddVar("CA", m_char->GetStats().agility.Total());
		P.AddVar("CW", m_char->GetStats().wisdom.Total());
		P.AddVar("CC", m_char->GetStats().chance.Total());
		P.AddVar("CS", m_char->GetStats().strength.Total());
		P.AddVar("CT", m_char->GetStats().tackleBlock.base);
		P.AddVar("Ct", m_char->GetStats().tackleEvade.base);

		if(full)
		{
			P.AddVar("Ci", m_char->GetStats().intelligence.base);
			P.AddVar("Cv", m_char->GetStats().vitality.base);
			P.AddVar("Ca", m_char->GetStats().agility.base);
			P.AddVar("Cw", m_char->GetStats().wisdom.base);
			P.AddVar("Cc", m_char->GetStats().chance.base);
			P.AddVar("Cs", m_char->GetStats().strength.base);
			P.AddVar("Ps", m_char->GetStats().GetAlignmentSide());
			P.AddVar("Pa", m_char->GetStats().GetAlignmentValue());
			P.AddVar("PP", m_char->GetStats().GetAlignmentGrade());
			P.AddVar("PL", m_char->GetLevel());
			P.AddVar("PK", m_char->GetStats().GetKamas());
			P.AddVar("PG", m_char->GetBreed());
			P.AddVar("PS", m_char->GetSex());
			P.AddVar("PZ", S->GetSubscriptionEnd() > 0 ? 1 : 0);
		}
	}
}