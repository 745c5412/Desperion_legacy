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

#ifndef __PLAYER_ITEM__
#define __PLAYER_ITEM__

enum CharacterInventoryPositionEnum
{
	ACCESSORY_POSITION_HAT = 6,
    ACCESSORY_POSITION_CAPE = 7,
    ACCESSORY_POSITION_BELT = 3,
    ACCESSORY_POSITION_BOOTS = 5,
    ACCESSORY_POSITION_AMULET = 0,
    ACCESSORY_POSITION_SHIELD = 15,
    ACCESSORY_POSITION_WEAPON = 1,
    ACCESSORY_POSITION_PETS = 8,
    INVENTORY_POSITION_RING_LEFT = 2,
    INVENTORY_POSITION_RING_RIGHT = 4,
    INVENTORY_POSITION_DOFUS_1 = 9,
    INVENTORY_POSITION_DOFUS_2 = 10,
    INVENTORY_POSITION_DOFUS_3 = 11,
    INVENTORY_POSITION_DOFUS_4 = 12,
    INVENTORY_POSITION_DOFUS_5 = 13,
    INVENTORY_POSITION_DOFUS_6 = 14,
    INVENTORY_POSITION_MOUNT = 16,
    INVENTORY_POSITION_MUTATION = 20,
    INVENTORY_POSITION_BOOST_FOOD = 21,
    INVENTORY_POSITION_FIRST_BONUS = 22,
    INVENTORY_POSITION_SECOND_BONUS = 23,
    INVENTORY_POSITION_FIRST_MALUS = 24,
    INVENTORY_POSITION_SECOND_MALUS = 25,
    INVENTORY_POSITION_ROLEPLAY_BUFFER = 26,
    INVENTORY_POSITION_FOLLOWER = 27,
    INVENTORY_POSITION_NOT_EQUIPED = 63,
};

class ObjectEffect;
class ObjectEffectDice;
class ObjectEffectInteger;

typedef boost::shared_ptr<ObjectEffect> ObjectEffectPtr;

struct PlayerItemEffect
{
	int16 actionId;

	PlayerItemEffect()
	{}

	PlayerItemEffect(int16 action)
	{
		actionId = action;
	}

	virtual ObjectEffectPtr ToObjectEffect()
	{ return ObjectEffectPtr(new ObjectEffect(this)); }

	virtual PlayerItemEffect* Clone()
	{
		return new PlayerItemEffect(actionId);
	}
};

struct PlayerItemEffectInteger : public PlayerItemEffect
{
	int16 value;

	PlayerItemEffectInteger()
	{}

	PlayerItemEffectInteger(int16 action, int16 val)
		: PlayerItemEffect(action)
	{
		value = val;
	}

	ObjectEffectPtr ToObjectEffect()
	{ return ObjectEffectPtr(new ObjectEffectInteger(this)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectInteger(actionId, value);
	}
};

struct PlayerItemEffectDice : public PlayerItemEffect
{
	int16 diceNum;
	int16 diceSide;
	int16 diceConst;

	PlayerItemEffectDice()
	{}

	PlayerItemEffectDice(int16 action, int16 dNum, int16 dSide, int16 dConst)
		: PlayerItemEffect(action)
	{
		diceNum = dNum;
		diceSide = dSide;
		diceConst = dConst;
	}

	ObjectEffectPtr ToObjectEffect()
	{ return ObjectEffectPtr(new ObjectEffectDice(this)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectDice(actionId, diceNum, diceSide, diceConst);
	}
};

inline PlayerItemEffect* G(std::string& str)
{
	std::vector<int16> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt, true);
	switch(table[0])
	{
	case OBJECT_EFFECT_DICE:
		return new PlayerItemEffectDice(table[1], table[2], table[3], table[4]);
	case OBJECT_EFFECT_INTEGER:
		return new PlayerItemEffectInteger(table[1], table[2]);
	case OBJECT_EFFECT:
	default:
		return new PlayerItemEffect(table[1]);
	}
}

class PlayerItem
{
private:
	static Mutex m_guidLock;
	int m_guid;
	int m_quantity;
	uint8 m_pos;
	Item* m_item;
	Character* m_owner;
	std::vector<PlayerItemEffect*> m_effects;
public:
	~PlayerItem();
	void Init(Field*);
	void Init(int, const Item*, int, uint8, const std::vector<PlayerItemEffect*>&, Character*);
	void Save();
	void SetPos(int);
	static int GetNextItemGuid();
	static void InsertIntoDB(PlayerItem*);
	static void DeleteFromDB(int);
	std::string StatsToString();

	Character* GetOwner()
	{ return m_owner; }

	void SetOwner(Character* c)
	{ m_owner = c; }

	int GetGuid() const
	{ return m_guid; }

	const Item* GetItem() const
	{ return m_item; }

	int GetQuantity() const
	{ return m_quantity; }

	uint8 GetPos() const
	{ return m_pos; }

	void SetQuantity(int q)
	{ m_quantity = q; }

	const std::vector<PlayerItemEffect*>& GetEffects() const
	{ return m_effects; }
};

#endif