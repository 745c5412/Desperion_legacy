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
	{
	}

	PlayerItemEffect(int16 actionId) : actionId(actionId)
	{
	}

	virtual ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffect(actionId)); }

	virtual PlayerItemEffect* Clone()
	{
		return new PlayerItemEffect(actionId);
	}

	virtual bool IsInteger() const
	{ return false; }

	virtual bool IsDice() const
	{ return false; }

	virtual bool IsString() const
	{ return false; }

	virtual bool IsMount() const
	{ return false; }

	virtual bool IsMinMax() const
	{ return false; }

	virtual bool IsLadder() const
	{ return false; }

	virtual bool IsDuration() const
	{ return false; }

	virtual bool IsDate() const
	{ return false; }

	virtual bool IsCreature() const
	{ return false; }
};

struct PlayerItemEffectInteger : public PlayerItemEffect
{
	int16 value;

	PlayerItemEffectInteger()
	{
	}

	PlayerItemEffectInteger(int16 actionId, int16 value) : PlayerItemEffect(actionId),
		value(value)
	{
	}

	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectInteger(actionId, value)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectInteger(actionId, value);
	}

	bool IsInteger() const
	{ return true; }
};

struct PlayerItemEffectDice : public PlayerItemEffect
{
	int16 diceNum, diceSide, diceConst;

	PlayerItemEffectDice()
	{
	}

	PlayerItemEffectDice(int16 actionId, int16 diceNum, int16 diceSide, int16 diceConst)
		: PlayerItemEffect(actionId), diceNum(diceNum), diceConst(diceConst)
	{
	}

	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectDice(actionId, diceNum, diceSide, diceConst)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectDice(actionId, diceNum, diceSide, diceConst);
	}

	bool IsDice() const
	{ return true; }
};

struct PlayerItemEffectString : public PlayerItemEffect
{
	std::string value;

	PlayerItemEffectString()
	{
	}

	PlayerItemEffectString(int16 actionId, std::string value) : PlayerItemEffect(actionId),
		value(value)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectString(actionId, value)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectString(actionId, value);
	}

	bool IsString() const
	{ return true; }
};

struct PlayerItemEffectMount : public PlayerItemEffect
{
	int mountId;
	time_t date;
	int16 modelId;

	PlayerItemEffectMount()
	{
	}

	PlayerItemEffectMount(int16 actionId, int mountId, time_t date, int16 modelId)
		: PlayerItemEffect(actionId), mountId(mountId), date(date), modelId(modelId)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectMount(actionId, mountId, date, modelId)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectMount(actionId, mountId, date, modelId);
	}

	bool IsMount() const
	{ return true; }
};

struct PlayerItemEffectMinMax : public PlayerItemEffect
{
	int16 min, max;

	PlayerItemEffectMinMax()
	{
	}

	PlayerItemEffectMinMax(int16 actionId, int16 min, int16 max) : PlayerItemEffect(actionId),
		min(min), max(max)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectMinMax(actionId, min, max)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectMinMax(actionId, min, max);
	}

	bool IsMinMax() const
	{ return true; }
};

struct PlayerItemEffectCreature : public PlayerItemEffect
{
	int16 monsterFamilyId;

	PlayerItemEffectCreature()
	{
	}

	PlayerItemEffectCreature(int16 actionId, int16 monsterFamilyId) : PlayerItemEffect(actionId),
		monsterFamilyId(monsterFamilyId)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectCreature(actionId, monsterFamilyId)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectCreature(actionId, monsterFamilyId);
	}

	bool IsCreature() const
	{ return true; }
};

struct PlayerItemEffectLadder : public PlayerItemEffectCreature
{
	int monsterCount;

	PlayerItemEffectLadder()
	{
	}

	PlayerItemEffectLadder(int16 actionId, int16 monsterFamilyId, int monsterCount)
		: PlayerItemEffectCreature(actionId, monsterFamilyId), monsterCount(monsterCount)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectLadder(actionId, monsterFamilyId, monsterCount)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectLadder(actionId, monsterFamilyId, monsterCount);
	}
	
	bool IsLadder() const
	{ return true; }
};

struct PlayerItemEffectDuration : public PlayerItemEffect
{
	int16 days, hours, minutes;

	PlayerItemEffectDuration()
	{
	}

	PlayerItemEffectDuration(int16 actionId, int16 days, int16 hours, int16 minutes)
		: PlayerItemEffect(actionId), days(days), hours(hours), minutes(minutes)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectDuration(actionId, days, hours, minutes)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectDuration(actionId, days, hours, minutes);
	}

	bool IsDuration() const
	{ return true; }
};

struct PlayerItemEffectDate : public PlayerItemEffect
{
	int16 year, month, day, hour, minute;

	PlayerItemEffectDate()
	{
	}

	PlayerItemEffectDate(int16 actionId, int16 year, int16 month, int16 day, int16 hour, int16 minute)
		: PlayerItemEffect(actionId), year(year), month(month), day(day), hour(hour), minute(minute)
	{
	}
	
	ObjectEffectPtr ToObjectEffect() const
	{ return ObjectEffectPtr(new ObjectEffectDate(actionId, year, month, day, hour, minute)); }

	PlayerItemEffect* Clone()
	{
		return new PlayerItemEffectDate(actionId, year, month, day, hour, minute);
	}

	bool IsDate() const
	{ return true; }
};

inline PlayerItemEffect* G(std::string& str)
{
	std::vector<int16> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt, true);
	switch(table[0])
	{
	case OBJECT_EFFECT_CREATURE:
		return new PlayerItemEffectCreature(table[1], table[2]);
	case OBJECT_EFFECT_DATE:
		return new PlayerItemEffectDate(table[1], table[2], table[3], table[4], table[5], table[6]);
	case OBJECT_EFFECT_DURATION:
		return new PlayerItemEffectDuration(table[1], table[2], table[3], table[4]);
	case OBJECT_EFFECT_LADDER:
		return new PlayerItemEffectLadder(table[1], table[2], table[3]);
	case OBJECT_EFFECT_MIN_MAX:
		return new PlayerItemEffectMinMax(table[1], table[2], table[3]);
	case OBJECT_EFFECT_MOUNT:
		return new PlayerItemEffectMount(table[1], table[2], table[3], table[4]);
	case OBJECT_EFFECT_STRING:
		{
			std::vector<std::string> strTable;
			Desperion::FastSplitString<','>(strTable, str, true);
			return new PlayerItemEffectString(table[1], strTable[2]);
		}
	case OBJECT_EFFECT_DICE:
		return new PlayerItemEffectDice(table[1], table[2], table[3], table[4]);
	case OBJECT_EFFECT_INTEGER:
		return new PlayerItemEffectInteger(table[1], table[2]);
	case OBJECT_EFFECT:
	default:
		return new PlayerItemEffect(table[1]);
	}
}

class Item;

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
	static bool SameStats(PlayerItem*, PlayerItem*);
	std::string StatsToString();
	PlayerItemEffect* GetEffect(int16);
	void DeleteEffect(int16);
	ObjectItem* ToObjectItem() const;

	void AddEffect(PlayerItemEffect* effect)
	{ m_effects.push_back(effect); }

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