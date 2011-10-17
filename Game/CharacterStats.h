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

#ifndef __CHARACTER_STATS__
#define __CHARACTER_STATS__

struct StatsRow
{
	int16 base;
	int16 objects;
	int16 align;
	int16 context;

	int16 Total() const
	{
		return base + objects + align + context;
	}

	StatsRow()
	{
		base = 0;
		objects = 0;
		align = 0;
		context = 0;
	}

	operator ByteBuffer() const
	{
		return CharacterBaseCharacteristic(base, objects, align, context);
	}
};

class CharacterStats
{
private:
	uint64 m_xp;
	int m_kamas;
	int m_statsPoints;
	int m_spellsPoints;

	int8 m_alignmentSide;
	int8 m_alignmentValue;
	int8 m_alignmentGrade;
	uint16 m_dishonor;
	int m_characterPower;
	uint16 m_honor;
	bool m_pvpEnabled;
	
	int16 m_usedAp;
	int16 m_usedMp;
	uint8 m_startLife;
	int16 m_energy;
	int m_damages;
public:
	int16 GetEnergy() const
	{ return m_energy; }

	int8 GetAlignmentSide() const
	{ return m_alignmentSide; }

	int8 GetAlignmentValue() const
	{ return m_alignmentValue; }

	int8 GetAlignmentGrade() const
	{ return m_alignmentGrade; }

	uint16 GetDishonor() const
	{ return m_dishonor; }

	int GetCharacterPower() const
	{ return m_characterPower; }

	uint16 GetHonor() const
	{ return m_honor; }

	bool IsPvpEnabled() const
	{ return m_pvpEnabled; }

	int GetStatsPoints() const
	{ return m_statsPoints; }

	int GetSpellsPoints() const
	{ return m_spellsPoints; }

	uint64 GetXp() const
	{ return m_xp; }

	int GetDamages() const
	{ return m_damages; }

	void Init(Field* fields, uint8 level)
	{
		m_kamas = fields[15].GetInt32();
		m_statsPoints = fields[16].GetInt32();
		m_spellsPoints = fields[17].GetInt32();
		m_alignmentSide = fields[18].GetInt8();
		m_alignmentValue = fields[19].GetInt8();
		m_alignmentGrade = fields[20].GetInt8();
		m_characterPower = fields[21].GetInt32();
		m_dishonor = fields[22].GetInt16();
		m_honor = fields[23].GetInt16();
		m_pvpEnabled = fields[24].GetBool();
		m_energy = fields[25].GetInt16();
		vitality.base = fields[26].GetInt16();
		wisdom.base = fields[27].GetInt16();
		strength.base = fields[28].GetInt16();
		intelligence.base = fields[29].GetInt16();
		chance.base = fields[30].GetInt16();
		agility.base = fields[31].GetInt16();
		m_xp = fields[32].GetUInt64();
		m_damages = fields[33].GetInt32();

		initiative.base += strength.base;
		initiative.base += intelligence.base;
		initiative.base += chance.base;
		initiative.base += agility.base;
		
		m_startLife = fields[36].GetUInt8();
		prospecting.base = fields[38].GetInt16();
		prospecting.base += (chance.Total() / 10);
		actionPoints.base = (level > 100 ? 7 : 6);
		movementPoints.base = 3;
		weightBonus = 0;

		m_usedAp = 0;
		m_usedMp = 0;
	}

	uint8 GetStartLife() const
	{ return m_startLife; }

	int16 GetCurrentAp() const
	{ return actionPoints.Total() - m_usedAp; }

	int16 GetCurrentMp() const
	{ return movementPoints.Total() - m_usedMp; }

	int GetKamas() const
	{ return m_kamas; }

	void AddObjectBonus(int effectId, int value)
	{
		StatsRow* stat = NULL;
		switch(effectId)
		{
		}
		if(stat != NULL)
			stat->objects += value;
	}

	uint16 weightBonus;
	StatsRow initiative;
    StatsRow prospecting;
    StatsRow actionPoints;
    StatsRow movementPoints;
    StatsRow strength;
    StatsRow vitality;
    StatsRow wisdom;
    StatsRow chance;
    StatsRow agility;
    StatsRow intelligence;
    StatsRow range;
    StatsRow summonableCreaturesBoost;
    StatsRow reflect;
    StatsRow criticalHit;
    StatsRow criticalMiss;
    StatsRow healBonus;
    StatsRow allDamagesBonus;
    StatsRow weaponDamagesBonusPercent;
    StatsRow damagesBonusPercent;
	StatsRow trapBonus;
    StatsRow trapBonusPercent;
    StatsRow permanentDamagePercent;
    StatsRow tackleBlock;
    StatsRow tackleEvade;
    StatsRow PAAttack;
    StatsRow PMAttack;
    StatsRow pushDamageBonus;
    StatsRow criticalDamageBonus;
    StatsRow neutralDamageBonus;
    StatsRow earthDamageBonus;
    StatsRow waterDamageBonus;
    StatsRow airDamageBonus;
    StatsRow fireDamageBonus;
    StatsRow dodgePALostProbability;
    StatsRow dodgePMLostProbability;
    StatsRow neutralElementResistPercent;
    StatsRow earthElementResistPercent;
    StatsRow waterElementResistPercent;
    StatsRow airElementResistPercent;
    StatsRow fireElementResistPercent;
    StatsRow neutralElementReduction;
    StatsRow earthElementReduction;
    StatsRow waterElementReduction;
    StatsRow airElementReduction;
    StatsRow fireElementReduction;
    StatsRow pushDamageReduction;
    StatsRow criticalDamageReduction;
    StatsRow pvpNeutralElementResistPercent;
    StatsRow pvpEarthElementResistPercent;
    StatsRow pvpWaterElementResistPercent;
    StatsRow pvpAirElementResistPercent;
    StatsRow pvpFireElementResistPercent;
    StatsRow pvpNeutralElementReduction;
    StatsRow pvpEarthElementReduction;
    StatsRow pvpWaterElementReduction;
    StatsRow pvpAirElementReduction;
    StatsRow pvpFireElementReduction;
};

#endif