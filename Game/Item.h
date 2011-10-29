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

#ifndef __ITEM__
#define __ITEM__

struct EffectInstance
{
	EffectInstance()
	{}

	EffectInstance(int effect, int target, int dur, int rand, bool hid, int zSize, int zShape)
	{
		effectId = effect;
		targetId = target;
		duration = dur;
		random = rand;
		hidden = hid;
		zoneSize = zSize;
		zoneShape = zShape;
	}

	int effectId;
	int targetId;
	int duration;
	int random;
	bool hidden;
	int zoneSize;
	int zoneShape;
};

struct EffectInstanceInteger : public EffectInstance
{
	EffectInstanceInteger()
	{}

	EffectInstanceInteger(int effect, int target, int dur, int rand, bool hid, int zSize, int zShape, int val)
		: EffectInstance(effect, target, dur, rand, hid, zSize, zShape)
	{
		value = val;
	}

	int value;
};

struct EffectInstanceDice : public EffectInstanceInteger
{
	EffectInstanceDice()
	{}

	EffectInstanceDice(int effect, int target, int dur, int rand, bool hid, int zSize, int zShape, int val, int dNum, int dSide)
		: EffectInstanceInteger(effect, target, dur, rand, hid, zSize, zShape, val)
	{
		diceNum = dNum;
		diceSide = dSide;
	}

	int diceNum;
	int diceSide;
};

inline EffectInstance&& F(std::string& str)
{
	std::vector<int> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt);
	return EffectInstanceDice(table[3], table[7], table[2], table[6], table[3] == 1, table[8],
		table[9], table[5], table[1], table[4]);
}

class Item
{
protected:
	int16 m_id;
	int m_typeId;
	int m_level;
	int m_weight;
	bool m_cursed;
	int m_useAnimationId;
	bool m_usable;
	bool m_targetable;
	int m_price;
	bool m_twoHanded;
	bool m_etheral;
	int m_itemSetId;
	std::string m_criteria;
	int m_appearanceId;
	std::vector<EffectInstance> m_possibleEffects;
	std::vector<int> m_favoriteSubAreas;
	int m_favoriteSubAreaBonus;
public:
	virtual ~Item() {}
	Item() {}
	virtual void Init(Field*);

	int GetLevel() const
	{ return m_level; }

	int GetTypeId() const
	{ return m_typeId; }

	std::string GetCriteria() const
	{ return m_criteria; }

	int GetItemSetId() const
	{ return m_itemSetId; }

	int GetWeight() const
	{ return m_weight; }

	int16 GetId() const
	{ return m_id; }

	int GetAppearanceId() const
	{ return m_appearanceId; }

	virtual bool IsWeapon() const
	{ return false; }
};

#endif