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

CharacterStats::EffectMap CharacterStats::m_effects;

void CharacterStats::InitEffectsTable()
{
	// +resistance % all (bond par exemple, mais je doute que cette stat soit utilisee dans les effets d'items)
	m_effects.insert(std::make_pair(1076, Effect(true, &CharacterStats::waterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1076, Effect(true, &CharacterStats::fireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1076, Effect(true, &CharacterStats::airElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1076, Effect(true, &CharacterStats::earthElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1076, Effect(true, &CharacterStats::neutralElementResistPercent, 1)));

	// -resistance % all
	m_effects.insert(std::make_pair(1077, Effect(false, &CharacterStats::waterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1077, Effect(false, &CharacterStats::fireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1077, Effect(false, &CharacterStats::airElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1077, Effect(false, &CharacterStats::earthElementResistPercent, 1)));
	m_effects.insert(std::make_pair(1077, Effect(false, &CharacterStats::neutralElementResistPercent, 1)));

	m_effects.insert(std::make_pair(430, Effect(true, &CharacterStats::neutralDamageBonus, 1)));
	m_effects.insert(std::make_pair(431, Effect(false, &CharacterStats::neutralDamageBonus, 1)));

	m_effects.insert(std::make_pair(428, Effect(true, &CharacterStats::airDamageBonus, 1)));
	m_effects.insert(std::make_pair(429, Effect(false, &CharacterStats::airDamageBonus, 1)));

	m_effects.insert(std::make_pair(426, Effect(true, &CharacterStats::waterDamageBonus, 1)));
	m_effects.insert(std::make_pair(427, Effect(false, &CharacterStats::waterDamageBonus, 1)));

	m_effects.insert(std::make_pair(424, Effect(true, &CharacterStats::fireDamageBonus, 1)));
	m_effects.insert(std::make_pair(425, Effect(false, &CharacterStats::fireDamageBonus, 1)));

	m_effects.insert(std::make_pair(422, Effect(true, &CharacterStats::earthDamageBonus, 1)));
	m_effects.insert(std::make_pair(423, Effect(false, &CharacterStats::earthDamageBonus, 1)));

	m_effects.insert(std::make_pair(420, Effect(true, &CharacterStats::criticalDamageReduction, 1)));
	m_effects.insert(std::make_pair(421, Effect(false, &CharacterStats::criticalDamageReduction, 1)));

	m_effects.insert(std::make_pair(418, Effect(true, &CharacterStats::criticalDamageBonus, 1)));
	m_effects.insert(std::make_pair(419, Effect(false, &CharacterStats::criticalDamageBonus, 1)));

	m_effects.insert(std::make_pair(416, Effect(true, &CharacterStats::pushDamageReduction, 1)));
	m_effects.insert(std::make_pair(417, Effect(false, &CharacterStats::pushDamageReduction, 1)));

	m_effects.insert(std::make_pair(414, Effect(true, &CharacterStats::pushDamageBonus, 1)));
	m_effects.insert(std::make_pair(415, Effect(false, &CharacterStats::pushDamageBonus, 1)));

	m_effects.insert(std::make_pair(412, Effect(true, &CharacterStats::PMAttack, 1)));
	m_effects.insert(std::make_pair(413, Effect(false, &CharacterStats::PMAttack, 1)));

	m_effects.insert(std::make_pair(410, Effect(true, &CharacterStats::PAAttack, 1)));
	m_effects.insert(std::make_pair(411, Effect(false, &CharacterStats::PAAttack, 1)));

	m_effects.insert(std::make_pair(753, Effect(true, &CharacterStats::tackleBlock, 1)));
	m_effects.insert(std::make_pair(755, Effect(false, &CharacterStats::tackleBlock, 1)));

	m_effects.insert(std::make_pair(752, Effect(true, &CharacterStats::tackleEvade, 1)));
	m_effects.insert(std::make_pair(754, Effect(false, &CharacterStats::tackleEvade, 1)));

	m_effects.insert(std::make_pair(225, Effect(true, &CharacterStats::trapBonus, 1)));
	m_effects.insert(std::make_pair(226, Effect(true, &CharacterStats::trapBonusPercent, 1)));

	// bizarrement, il n'y a que les effets positifs pour les pvpElementReduction
	m_effects.insert(std::make_pair(264, Effect(true, &CharacterStats::pvpNeutralElementReduction, 1)));
	m_effects.insert(std::make_pair(262, Effect(true, &CharacterStats::pvpAirElementReduction, 1)));
	m_effects.insert(std::make_pair(261, Effect(true, &CharacterStats::pvpWaterElementReduction, 1)));
	m_effects.insert(std::make_pair(263, Effect(true, &CharacterStats::pvpFireElementReduction, 1)));
	m_effects.insert(std::make_pair(260, Effect(true, &CharacterStats::pvpEarthElementReduction, 1)));

	m_effects.insert(std::make_pair(254, Effect(true, &CharacterStats::pvpNeutralElementResistPercent, 1)));
	m_effects.insert(std::make_pair(252, Effect(true, &CharacterStats::pvpAirElementResistPercent, 1)));
	m_effects.insert(std::make_pair(251, Effect(true, &CharacterStats::pvpWaterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(253, Effect(true, &CharacterStats::pvpFireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(250, Effect(true, &CharacterStats::pvpEarthElementResistPercent, 1)));

	m_effects.insert(std::make_pair(259, Effect(false, &CharacterStats::pvpNeutralElementResistPercent, 1)));
	m_effects.insert(std::make_pair(257, Effect(false, &CharacterStats::pvpAirElementResistPercent, 1)));
	m_effects.insert(std::make_pair(256, Effect(false, &CharacterStats::pvpWaterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(258, Effect(false, &CharacterStats::pvpFireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(255, Effect(false, &CharacterStats::pvpEarthElementResistPercent, 1)));

	m_effects.insert(std::make_pair(244, Effect(true, &CharacterStats::neutralElementReduction, 1)));
	m_effects.insert(std::make_pair(242, Effect(true, &CharacterStats::airElementReduction, 1)));
	m_effects.insert(std::make_pair(241, Effect(true, &CharacterStats::waterElementReduction, 1)));
	m_effects.insert(std::make_pair(243, Effect(true, &CharacterStats::fireElementReduction, 1)));
	m_effects.insert(std::make_pair(244, Effect(true, &CharacterStats::earthElementReduction, 1)));

	m_effects.insert(std::make_pair(249, Effect(false, &CharacterStats::neutralElementReduction, 1)));
	m_effects.insert(std::make_pair(247, Effect(false, &CharacterStats::airElementReduction, 1)));
	m_effects.insert(std::make_pair(246, Effect(false, &CharacterStats::waterElementReduction, 1)));
	m_effects.insert(std::make_pair(240, Effect(false, &CharacterStats::fireElementReduction, 1)));
	m_effects.insert(std::make_pair(245, Effect(false, &CharacterStats::earthElementReduction, 1)));

	m_effects.insert(std::make_pair(220, Effect(true, &CharacterStats::reflect, 1)));

	m_effects.insert(std::make_pair(178, Effect(true, &CharacterStats::healBonus, 1)));
	m_effects.insert(std::make_pair(179, Effect(false, &CharacterStats::healBonus, 1)));

	m_effects.insert(std::make_pair(176, Effect(true, &CharacterStats::prospecting, 1)));
	m_effects.insert(std::make_pair(177, Effect(false, &CharacterStats::prospecting, 1)));

	m_effects.insert(std::make_pair(174, Effect(true, &CharacterStats::initiative, 1)));
	m_effects.insert(std::make_pair(175, Effect(false, &CharacterStats::initiative, 1)));

	m_effects.insert(std::make_pair(122, Effect(true, &CharacterStats::criticalMiss, 1)));

	m_effects.insert(std::make_pair(214, Effect(true, &CharacterStats::neutralElementResistPercent, 1)));
	m_effects.insert(std::make_pair(212, Effect(true, &CharacterStats::airElementResistPercent, 1)));
	m_effects.insert(std::make_pair(211, Effect(true, &CharacterStats::waterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(213, Effect(true, &CharacterStats::fireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(210, Effect(true, &CharacterStats::earthElementResistPercent, 1)));

	m_effects.insert(std::make_pair(219, Effect(false, &CharacterStats::neutralElementResistPercent, 1)));
	m_effects.insert(std::make_pair(217, Effect(false, &CharacterStats::airElementResistPercent, 1)));
	m_effects.insert(std::make_pair(216, Effect(false, &CharacterStats::waterElementResistPercent, 1)));
	m_effects.insert(std::make_pair(218, Effect(false, &CharacterStats::fireElementResistPercent, 1)));
	m_effects.insert(std::make_pair(215, Effect(false, &CharacterStats::earthElementResistPercent, 1)));

	m_effects.insert(std::make_pair(161, Effect(true, &CharacterStats::dodgePMLostProbability, 1)));
	m_effects.insert(std::make_pair(163, Effect(false, &CharacterStats::dodgePMLostProbability, 1)));

	m_effects.insert(std::make_pair(160, Effect(true, &CharacterStats::dodgePALostProbability, 1)));
	m_effects.insert(std::make_pair(162, Effect(false, &CharacterStats::dodgePALostProbability, 1)));

	m_effects.insert(std::make_pair(182, Effect(true, &CharacterStats::summonableCreaturesBoost, 1)));

	m_effects.insert(std::make_pair(128, Effect(true, &CharacterStats::movementPoints, 1)));
	m_effects.insert(std::make_pair(127, Effect(false, &CharacterStats::movementPoints, 1)));

	// +reduc physique (neutre et terre) --> obsolete mais je met quand meme, on sait jamais :)
	m_effects.insert(std::make_pair(184, Effect(true, &CharacterStats::neutralElementReduction, 1)));
	m_effects.insert(std::make_pair(184, Effect(true, &CharacterStats::earthElementReduction, 1)));

	// -reduc physique
	m_effects.insert(std::make_pair(173, Effect(false, &CharacterStats::neutralElementReduction, 1)));
	m_effects.insert(std::make_pair(173, Effect(false, &CharacterStats::earthElementReduction, 1)));

	// +reduc magique (air, eau et feu) --> idem
	m_effects.insert(std::make_pair(183, Effect(true, &CharacterStats::airElementReduction, 1)));
	m_effects.insert(std::make_pair(183, Effect(true, &CharacterStats::waterElementReduction, 1)));
	m_effects.insert(std::make_pair(183, Effect(true, &CharacterStats::fireElementReduction, 1)));

	// -reduc magique
	m_effects.insert(std::make_pair(172, Effect(false, &CharacterStats::airElementReduction, 1)));
	m_effects.insert(std::make_pair(172, Effect(false, &CharacterStats::waterElementReduction, 1)));
	m_effects.insert(std::make_pair(172, Effect(false, &CharacterStats::fireElementReduction, 1)));

	m_effects.insert(std::make_pair(117, Effect(true, &CharacterStats::range, 1)));
	m_effects.insert(std::make_pair(116, Effect(false, &CharacterStats::range, 1)));

	m_effects.insert(std::make_pair(115, Effect(true, &CharacterStats::criticalHit, 1)));
	m_effects.insert(std::make_pair(171, Effect(false, &CharacterStats::criticalHit, 1)));

	// 114 c'est: "multiplie les dommages par X", obsolete mais bon, comme d'hab
	m_effects.insert(std::make_pair(114, Effect(true, &CharacterStats::damagesBonusPercent, 1)));
	m_effects.insert(std::make_pair(138, Effect(true, &CharacterStats::damagesBonusPercent, 1)));
	m_effects.insert(std::make_pair(186, Effect(false, &CharacterStats::damagesBonusPercent, 1)));

	// +dom normaux (sur les items "post-frigost"); y'a plusieurs valeurs dans le fichier des Effects, donc je suis pas sur
	m_effects.insert(std::make_pair(112, Effect(true, &CharacterStats::allDamagesBonus, 1)));
	m_effects.insert(std::make_pair(145, Effect(false, &CharacterStats::allDamagesBonus, 1)));

	m_effects.insert(std::make_pair(126, Effect(true, &CharacterStats::intelligence, 1)));
	m_effects.insert(std::make_pair(126, Effect(true, &CharacterStats::healBonus, 10)));
	m_effects.insert(std::make_pair(126, Effect(true, &CharacterStats::initiative, 1)));
	m_effects.insert(std::make_pair(155, Effect(false, &CharacterStats::intelligence, 1)));
	m_effects.insert(std::make_pair(155, Effect(false, &CharacterStats::healBonus, 10)));
	m_effects.insert(std::make_pair(155, Effect(false, &CharacterStats::initiative, 1)));

	m_effects.insert(std::make_pair(119, Effect(true, &CharacterStats::agility, 1)));
	m_effects.insert(std::make_pair(119, Effect(true, &CharacterStats::tackleBlock, 10)));
	m_effects.insert(std::make_pair(119, Effect(true, &CharacterStats::tackleEvade, 10)));
	m_effects.insert(std::make_pair(119, Effect(true, &CharacterStats::initiative, 1)));
	m_effects.insert(std::make_pair(154, Effect(false, &CharacterStats::agility, 1)));
	m_effects.insert(std::make_pair(154, Effect(false, &CharacterStats::tackleBlock, 10)));
	m_effects.insert(std::make_pair(154, Effect(false, &CharacterStats::tackleEvade, 10)));
	m_effects.insert(std::make_pair(154, Effect(false, &CharacterStats::initiative, 1)));

	m_effects.insert(std::make_pair(123, Effect(true, &CharacterStats::chance, 1)));
	m_effects.insert(std::make_pair(123, Effect(true, &CharacterStats::prospecting, 10)));
	m_effects.insert(std::make_pair(123, Effect(true, &CharacterStats::initiative, 1)));
	m_effects.insert(std::make_pair(152, Effect(false, &CharacterStats::chance, 1)));
	m_effects.insert(std::make_pair(152, Effect(false, &CharacterStats::prospecting, 10)));
	m_effects.insert(std::make_pair(152, Effect(false, &CharacterStats::initiative, 1)));

	m_effects.insert(std::make_pair(124, Effect(true, &CharacterStats::wisdom, 1)));
	m_effects.insert(std::make_pair(124, Effect(true, &CharacterStats::dodgePALostProbability, 10)));
	m_effects.insert(std::make_pair(124, Effect(true, &CharacterStats::dodgePMLostProbability, 10)));
	m_effects.insert(std::make_pair(124, Effect(true, &CharacterStats::PAAttack, 10)));
	m_effects.insert(std::make_pair(124, Effect(true, &CharacterStats::PMAttack, 10)));
	m_effects.insert(std::make_pair(156, Effect(false, &CharacterStats::wisdom, 1)));
	m_effects.insert(std::make_pair(156, Effect(false, &CharacterStats::dodgePALostProbability, 10)));
	m_effects.insert(std::make_pair(156, Effect(false, &CharacterStats::dodgePMLostProbability, 10)));
	m_effects.insert(std::make_pair(156, Effect(false, &CharacterStats::PAAttack, 10)));
	m_effects.insert(std::make_pair(156, Effect(false, &CharacterStats::PMAttack, 10)));

	m_effects.insert(std::make_pair(125, Effect(true, &CharacterStats::vitality, 1)));
	m_effects.insert(std::make_pair(153, Effect(false, &CharacterStats::vitality, 1)));

	// les bonus de pods en fonction de la force sont gérés dans Character::GetTotalPods()
	m_effects.insert(std::make_pair(118, Effect(true, &CharacterStats::strength, 1)));
	m_effects.insert(std::make_pair(118, Effect(true, &CharacterStats::initiative, 1)));
	m_effects.insert(std::make_pair(157, Effect(false, &CharacterStats::strength, 1)));
	m_effects.insert(std::make_pair(157, Effect(false, &CharacterStats::initiative, 1)));

	m_effects.insert(std::make_pair(111, Effect(true, &CharacterStats::actionPoints, 1)));
	m_effects.insert(std::make_pair(168, Effect(false, &CharacterStats::actionPoints, 1)));
}