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

#ifndef __CHARACTER__
#define __CHARACTER__

class Session;
class PlayerItem;

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

class Character : public HumanEntity
{
private:
	Session* m_session;
	CharacterStats m_stats;
	uint8 m_level;
	int8 m_breed;
	bool m_sex;
	int m_account;
	//spells
	int m_saveMap;
	int16 m_saveCell;

	int16 m_nextCell;
	int8 m_nextDirection;
	//jobs
	int8 m_mountXp;
	//Mount*
	bool m_isDead;
	bool m_isMerchant;
	std::vector<int8> m_emotes;
	std::vector<int> m_zaaps;
	std::list<PlayerItem*> m_items;
	int8 m_context;

	void InitItems();
public:
	void Init(Field*, CharacterMinimals*, Session*);
	~Character();

	void DeleteItem(int, bool, bool);
	void AddItem(PlayerItem*);
	void MoveItem(PlayerItem*, uint8, bool create = false);
	void MoveItemFromMap(PlayerItem*);
	PlayerItem* GetSimilarItem(PlayerItem*);
	PlayerItem* GetItem(int);
	PlayerItem* GetItemByPos(uint8);
	bool HasEquiped(int16);
	//bool ApplyUsableEffect();
	bool ApplyEffect(double StatsRow::*, EffectInstanceInteger&, bool);
	bool ApplyEffect(double StatsRow::*, int, int, bool);
	std::vector<int16> GetItemsFromSet(int16);
	std::tr1::unordered_map<int16, std::vector<int16> > GetTotalItemSets();
	void UpdateItemSet(int16, boost::function<void()>);

	int8 GetNextDirection() const
	{ return m_nextDirection; }

	void SetNextDirection(int8 dir)
	{ m_nextDirection = dir; }

	int16 GetNextCell() const
	{ return m_nextCell; }

	void SetNextCell(int16 cell)
	{ m_nextCell = cell; }

	int8 GetContextType() const
	{ return m_context; }

	const std::list<PlayerItem*>& GetItems() const
	{ return m_items; }

	Session* GetSession()
	{ return m_session; }

	CharacterStats& GetStats()
	{ return m_stats; }

	int GetLevel() const
	{ return m_level; }

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

	bool IsCharacter() const
	{ return true; }

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

	virtual GameRolePlayActorInformationsPtr ToActor()
	{ return GameRolePlayActorInformationsPtr(new GameRolePlayCharacterInformations(this)); }

	void Save();
};

#endif