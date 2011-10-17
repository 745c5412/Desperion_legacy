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

CharacterCharacteristicsInformations::CharacterCharacteristicsInformations(Character* ch)
{
	m_buffer<<ch->GetStats().GetXp()<<uint64(0)<<uint64(0); // floor, ceil
	m_buffer<<ch->GetStats().GetKamas()<<ch->GetStats().GetStatsPoints()<<ch->GetStats().GetSpellsPoints();
	m_buffer<<ActorExtendedAlignmentInformations(ch->GetStats().GetAlignmentSide(), ch->GetStats().GetAlignmentValue(),
		ch->GetStats().GetAlignmentGrade(), ch->GetStats().GetDishonor(), ch->GetStats().GetCharacterPower(),
		ch->GetStats().GetHonor(), 0, 0, ch->GetStats().IsPvpEnabled());
	m_buffer<<ch->GetCurrentLife()<<ch->GetMaxLife()<<ch->GetStats().GetEnergy()<<int16(10000); // maxEnergy
	m_buffer<<ch->GetStats().GetCurrentAp()<<ch->GetStats().GetCurrentMp();

	m_buffer<<ch->GetStats().initiative<<ch->GetStats().prospecting<<ch->GetStats().actionPoints<<ch->GetStats().movementPoints;
	m_buffer<<ch->GetStats().strength<<ch->GetStats().vitality<<ch->GetStats().wisdom<<ch->GetStats().chance<<ch->GetStats().agility<<ch->GetStats().intelligence;
	m_buffer<<ch->GetStats().range<<ch->GetStats().summonableCreaturesBoost<<ch->GetStats().reflect<<ch->GetStats().criticalHit<<int16(50); // criticalHitWeapon
	m_buffer<<ch->GetStats().criticalMiss<<ch->GetStats().healBonus<<ch->GetStats().allDamagesBonus<<ch->GetStats().weaponDamagesBonusPercent<<ch->GetStats().damagesBonusPercent;
	m_buffer<<ch->GetStats().trapBonus<<ch->GetStats().trapBonusPercent<<ch->GetStats().permanentDamagePercent<<ch->GetStats().tackleBlock<<ch->GetStats().tackleEvade;
	m_buffer<<ch->GetStats().PAAttack<<ch->GetStats().PMAttack<<ch->GetStats().pushDamageBonus<<ch->GetStats().criticalDamageBonus<<ch->GetStats().neutralDamageBonus;
	m_buffer<<ch->GetStats().earthDamageBonus<<ch->GetStats().waterDamageBonus<<ch->GetStats().airDamageBonus<<ch->GetStats().fireDamageBonus;
	m_buffer<<ch->GetStats().dodgePALostProbability<<ch->GetStats().dodgePMLostProbability<<ch->GetStats().neutralElementResistPercent;
	m_buffer<<ch->GetStats().earthElementResistPercent<<ch->GetStats().waterElementResistPercent<<ch->GetStats().airElementResistPercent;
	m_buffer<<ch->GetStats().fireElementResistPercent<<ch->GetStats().neutralElementReduction<<ch->GetStats().earthElementReduction;
	m_buffer<<ch->GetStats().waterElementReduction<<ch->GetStats().airElementReduction<<ch->GetStats().fireElementReduction;
	m_buffer<<ch->GetStats().pushDamageReduction<<ch->GetStats().criticalDamageReduction<<ch->GetStats().pvpNeutralElementResistPercent;
	m_buffer<<ch->GetStats().pvpEarthElementResistPercent<<ch->GetStats().pvpWaterElementResistPercent<<ch->GetStats().pvpAirElementResistPercent;
	m_buffer<<ch->GetStats().pvpFireElementResistPercent<<ch->GetStats().pvpNeutralElementReduction<<ch->GetStats().pvpEarthElementReduction;
	m_buffer<<ch->GetStats().pvpWaterElementReduction<<ch->GetStats().pvpAirElementReduction<<ch->GetStats().pvpFireElementReduction;
	m_buffer<<uint16(0); // spellModifications
}