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

#ifndef __CHARACTER__
#define __CHARACTER__

class Session;
class PlayerItem;

enum Restriction
{
	cantBeAggressed,
	cantBeChallenged,
	cantTrade,
	cantBeAttackedByMutant,
	cantRun,
	forceSlowWalk,
	cantMinimize,
	cantMove,
	cantAggress,
	cantChallenge,
	cantExchange,
	cantAttack,
	cantChat,
	cantBeMerchant,
	cantUseObject,
	cantUseTaxCollector,
	cantUseInteractive,
	cantSpeakToNPC,
	cantChangeZone,
	cantAttackMonster,
	cantWalk8Directions,
	RESTRICTIONS_NUMBER,
};

enum Direction
{
	DIRECTION_EAST = 0,
	DIRECTION_SOUTH_EAST = 1,
	DIRECTION_SOUTH = 2,
	DIRECTION_SOUTH_WEST = 3,
	DIRECTION_WEST = 4,
	DIRECTION_NORTH_WEST = 5,
	DIRECTION_NORTH = 6,
	DIRECTION_NORTH_EAST = 7,
};

enum Breed
{
	UNDEFINED = 0,
	Feca = 1,
	Osamodas = 2,
	Enutrof = 3,
	Sram = 4,
	Xelor = 5,
	Ecaflip = 6,
	Eniripsa = 7,
	Iop = 8,
	Cra = 9,
	Sadida = 10,
	Sacrieur = 11,
	Pandawa = 12,
	Roublard = 13,
	Zobal = 14,
	SUMMONED = -1,
	MONSTER = -2,
	MONSTER_GROUP = -3,
	NPC = -4,
	HUMAN_VENDOR = -5,
	TAX_COLLECTOR = -6,
	MUTANT = -7,
	MUTANT_IN_DUNGEON = -8,
	MOUNT_OUTSIDE = -9,
	PRISM = -10,
};

enum GameContext
{
	ROLE_PLAY = 1,
	FIGHT = 2,
};

class Character
{
private:
	int m_guid;
	Session* m_session;
	DEntityLook m_look;
	CharacterStats m_stats;
	uint8 m_level;
	std::string m_name;
	int8 m_breed;
	bool m_sex;
	int m_account;
	int m_currentMap;
	int16 m_currentCell;
	//spells
	int m_saveMap;
	int16 m_saveCell;
	//jobs
	int8 m_mountXp;
	//Mount*
	bool m_isDead;
	int16 m_title;
	bool m_isMerchant;
	std::vector<int8> m_emotes;
	std::vector<int> m_zaaps;
	std::list<PlayerItem*> m_items;
	int8 m_context;
	int8 m_direction;
	bool m_restrictions[RESTRICTIONS_NUMBER];

	void InitItems();
public:
	void Init(Field*, CharacterMinimals*, Session*);
	~Character();

	int16 GetCurrentCell() const
	{ return m_currentCell; }

	int8 GetContextType() const
	{ return m_context; }

	const std::list<PlayerItem*>& GetItems() const
	{ return m_items; }

	Session* GetSession()
	{ return m_session; }

	int GetGuid() const
	{ return m_guid; }

	DEntityLook& GetLook()
	{ return m_look; }

	CharacterStats& GetStats()
	{ return m_stats; }

	int GetLevel() const
	{ return m_level; }

	std::string GetName() const
	{ return m_name; }

	int8 GetBreed() const
	{ return m_breed; }

	bool GetSex() const
	{ return m_sex; }

	int GetCurrentPods() const
	{
		int count = 0;
		for(std::list<PlayerItem*>::const_iterator it = m_items.begin(); it != m_items.end(); ++it)
			count += (*it)->GetItem()->GetWeight();
		return count;
	}
	
	int GetMaxPods() const
	{
		return 1000 + m_stats.strength.Total() * 5 + m_stats.weightBonus;
	}

	int GetMaxLife() const
	{
		return m_stats.GetStartLife() + m_stats.vitality.Total() + (m_level - 1) * 5;
	}

	int GetCurrentLife() const
	{
		int maxLife = GetMaxLife();
		int currentLife = maxLife - m_stats.GetDamages();
		if(currentLife < 0)
			currentLife = 0;
		return currentLife;
	}

	int GetCurrentMap() const
	{ return m_currentMap; }

	ByteBuffer SerializeActor() const;
	ByteBuffer SerializeStats() const;
};

#endif