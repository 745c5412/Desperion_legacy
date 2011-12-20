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

namespace DofusUtils
{
	int Truncate(double n)
	{
		double loc2 = std::pow(double(10), double(0));
		double loc3 = n * loc2;
		return static_cast<int>(static_cast<int>(loc3) / loc2);
	}

	int64 CalculateXpMonsters(double groupXp, double groupLevel, double highestMonsterLevel, double ageBonus, Character* ch,
		std::vector<Character*>& team, double mountRatio, double guildRatio)
	{
		// Calcul du niveau de la team, ainsi que du niveau du personnage le plus fort
		double totalTeamLevel = 0;
		double highestTeamLevel = 0;
		for(size_t a = 0; a < team.size(); ++a)
		{
			totalTeamLevel += team[a]->GetLevel();
			if(team[a]->GetLevel() > highestTeamLevel)
				highestTeamLevel = team[a]->GetLevel();
		}

		// Calcul du coefficient dû au niveau de la team par rapport au niveau du groupe de monstres
		double levelCoeff = 1;
		if(totalTeamLevel - 5 > groupLevel)
			levelCoeff = groupLevel / totalTeamLevel;
		else if(totalTeamLevel + 10 < groupLevel)
			levelCoeff = (totalTeamLevel + 10) / groupLevel;

		// pondération avec le niveau de ch
		double min = std::min(int(ch->GetLevel()), Truncate(2.5 * highestMonsterLevel));
		double loc16 = min / totalTeamLevel * 100;

		/*
			détermination d'un facteur de multiplication en fonction du nombre de personnes
			dans la team: chaque personnage de la team doit avoir un niveau supérieur à 
			(highestTeamLevel / 3) pour être considéré
		*/
		double teamFactors[8] = {1, 3, 4, 5, 6, 7, 8, 9};
		uint8 index = 0;
		for(size_t a = 0; a < team.size(); ++a)
		{
			if(team[a]->GetLevel() >= highestTeamLevel / 3)
				++index;
		}
		if(index == 0)
			index = 1;

		double loc20 = Truncate(groupXp * teamFactors[index - 1] * levelCoeff);
		double loc22 = Truncate(loc16 / 100 * loc20);

		double totalWisdom = ch->GetStats().wisdom.align + ch->GetStats().wisdom.base + ch->GetStats().wisdom.context + ch->GetStats().wisdom.objects;
		if(totalWisdom < 0)
			totalWisdom = 0;

		double ageCoeff = ageBonus <= 0 ? 1 : (1 + ageBonus / 100);
		double xp = Truncate(Truncate(loc22 * (100 + totalWisdom) / 100) * ageCoeff); // xp totale gagnée par ch

		// on retranche l'xp perdue à cause de la drago
		if(mountRatio > 0)
			xp -= Truncate(xp * mountRatio / 100);
		if(guildRatio > 0) // idem (la guilde passe après la drago)
			xp -= Truncate(xp * guildRatio / 100);

		// on oublie pas de multiplier par le facteur d'xp de la config :)
		return static_cast<int64>(Desperion::Config::Instance().GetParam(EXPERIENCE_FACTOR_STRING, EXPERIENCE_FACTOR_DEFAULT) * xp);
	}

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

		std::string vowels = "aeiouy";
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

	int16 GetObviAppearanceBySkinId(int skin, int type)
	{
		switch(type)
		{
		case 9233:
			return 1115 + skin;
		case 9234:
			return 1135 + skin;
		case 12425:
			return 1469 + skin;
		case 12424:
			return 1489 + skin;
		}
		return 0;
	}

	bool IsValidPlaceForItem(const Item* item, uint8 pos)
	{
		switch(item->GetId()) // pour les obvis
		{
		case 12424:
		case 9233:
			if(pos == ACCESSORY_POSITION_CAPE)
				return true;
			break;
		case 12425:
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
		case 12427:
			if(pos == ACCESSORY_POSITION_BELT)
				return true;
			break;
		case 12428:
			if(pos == ACCESSORY_POSITION_BOOTS)
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

	uint8 GetLevelByObviXp(int xp)
	{
		if(xp < 10)
			return 1;
		else if(xp < 21)
			return 2;
		else if(xp < 33)
			return 3;
		else if(xp < 46)
			return 4;
		else if(xp < 60)
			return 5;
		else if(xp < 75)
			return 6;
		else if(xp < 91)
			return 7;
		else if(xp < 108)
			return 8;
		else if(xp < 126)
			return 9;
		else if(xp < 145)
			return 10;
		else if(xp < 165)
			return 11;
		else if(xp < 186)
			return 12;
		else if(xp < 208)
			return 13;
		else if(xp < 231)
			return 14;
		else if(xp < 255)
			return 15;
		else if(xp < 280)
			return 16;
		else if(xp < 306)
			return 17;
		else if(xp < 333)
			return 18;
		else if(xp < 361)
			return 19;
		else
			return 20;
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

		if(full)
		{
			P.AddVar("Ci", static_cast<int64>(m_char->GetStats().intelligence.base));
			P.AddVar("Cv", static_cast<int64>(m_char->GetStats().vitality.base));
			P.AddVar("Ca", static_cast<int64>(m_char->GetStats().agility.base));
			P.AddVar("Cw", static_cast<int64>(m_char->GetStats().wisdom.base));
			P.AddVar("Cc", static_cast<int64>(m_char->GetStats().chance.base));
			P.AddVar("Cs", static_cast<int64>(m_char->GetStats().strength.base));
			P.AddVar("Ps", static_cast<int64>(m_char->GetStats().GetAlignmentSide()));
			P.AddVar("Pa", static_cast<int64>(m_char->GetStats().GetAlignmentValue()));
			P.AddVar("PP", static_cast<int64>(m_char->GetStats().GetAlignmentGrade()));
			P.AddVar("PL", static_cast<int64>(m_char->GetLevel()));
			P.AddVar("PK", static_cast<int64>(m_char->GetStats().GetKamas()));
			P.AddVar("PG", static_cast<int64>(m_char->GetBreed()));
			P.AddVar("PS", static_cast<int64>(m_char->GetSex()));
			P.AddVar("PZ", S->GetSubscriptionEnd() > 0 ? 1 : 0);
			P.AddVar("CT", static_cast<int64>(m_char->GetStats().tackleBlock.base));
			P.AddVar("Ct", static_cast<int64>(m_char->GetStats().tackleEvade.base));
		}
	}
}