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

#ifndef __CHARACTER_STATS__
#define __CHARACTER_STATS__

struct StatsRow
{
	double base;
	double objects;
	double align;
	double context;

	int16 Total() const
	{
		return int16(int64(base) & 0xffff) + int16(int64(objects) & 0xffff) + 
			int16(int64(align) & 0xffff) + int16(int64(context) & 0xffff);
	}

	StatsRow()
	{
		base = 0;
		objects = 0;
		align = 0;
		context = 0;
	}

	CharacterBaseCharacteristic* ToBase() const
	{
		return new CharacterBaseCharacteristic(int16(int64(base) & 0xffff), int16(int64(objects) & 0xffff), 
			int16(int64(align) & 0xffff), int16(int64(context) & 0xffff));
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
		m_dishonor = fields[21].GetInt16();
		m_honor = fields[22].GetInt16();
		m_pvpEnabled = fields[23].GetBool();
		m_energy = fields[24].GetInt16();
		
		m_xp = fields[31].GetUInt64();
		m_damages = fields[32].GetInt32();
		
		m_startLife = fields[35].GetUInt8();
		prospecting.base += fields[36].GetInt16();
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