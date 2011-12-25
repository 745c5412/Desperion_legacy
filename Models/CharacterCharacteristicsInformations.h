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

#ifndef __CHARACTER_CHARACTERISTICS_INFORMATIONS__
#define __CHARACTER_CHARACTERISTICS_INFORMATIONS__

class CharacterCharacteristicsInformations : public DofusModel
{
public:
	int64 experience;
	int64 experienceLevelFloor;
	int64 experienceNextLevelFloor;
	int kamas;
	int statsPoints;
	int spellsPoints;
	ActorExtendedAlignmentInformationsPtr alignmentInfos;
	int lifePoints;
	int maxLifePoints;
	int16 energyPoints;
	int16 maxEnergyPoints;
	int16 actionPointsCurrent;
	int16 movementPointsCurrent;
	CharacterBaseCharacteristicPtr initiative;
	CharacterBaseCharacteristicPtr prospecting;
	CharacterBaseCharacteristicPtr actionPoints;
	CharacterBaseCharacteristicPtr movementPoints;
	CharacterBaseCharacteristicPtr strength;
	CharacterBaseCharacteristicPtr vitality;
	CharacterBaseCharacteristicPtr wisdom;
	CharacterBaseCharacteristicPtr chance;
	CharacterBaseCharacteristicPtr agility;
	CharacterBaseCharacteristicPtr intelligence;
	CharacterBaseCharacteristicPtr range;
	CharacterBaseCharacteristicPtr summonableCreaturesBoost;
	CharacterBaseCharacteristicPtr reflect;
	CharacterBaseCharacteristicPtr criticalHit;
	int16 criticalHitWeapon;
	CharacterBaseCharacteristicPtr criticalMiss;
	CharacterBaseCharacteristicPtr healBonus;
	CharacterBaseCharacteristicPtr allDamagesBonus;
	CharacterBaseCharacteristicPtr weaponDamagesBonusPercent;
	CharacterBaseCharacteristicPtr damagesBonusPercent;
	CharacterBaseCharacteristicPtr trapBonus;
	CharacterBaseCharacteristicPtr trapBonusPercent;
	CharacterBaseCharacteristicPtr permanentDamagePercent;
	CharacterBaseCharacteristicPtr tackleBlock;
	CharacterBaseCharacteristicPtr tackleEvade;
	CharacterBaseCharacteristicPtr PAAttack;
	CharacterBaseCharacteristicPtr PMAttack;
	CharacterBaseCharacteristicPtr pushDamageBonus;
	CharacterBaseCharacteristicPtr criticalDamageBonus;
	CharacterBaseCharacteristicPtr neutralDamageBonus;
	CharacterBaseCharacteristicPtr earthDamageBonus;
	CharacterBaseCharacteristicPtr waterDamageBonus;
	CharacterBaseCharacteristicPtr airDamageBonus;
	CharacterBaseCharacteristicPtr fireDamageBonus;
	CharacterBaseCharacteristicPtr dodgePALostProbability;
	CharacterBaseCharacteristicPtr dodgePMLostProbability;
	CharacterBaseCharacteristicPtr neutralElementResistPercent;
	CharacterBaseCharacteristicPtr earthElementResistPercent;
	CharacterBaseCharacteristicPtr waterElementResistPercent;
	CharacterBaseCharacteristicPtr airElementResistPercent;
	CharacterBaseCharacteristicPtr fireElementResistPercent;
	CharacterBaseCharacteristicPtr neutralElementReduction;
	CharacterBaseCharacteristicPtr earthElementReduction;
	CharacterBaseCharacteristicPtr waterElementReduction;
	CharacterBaseCharacteristicPtr airElementReduction;
	CharacterBaseCharacteristicPtr fireElementReduction;
	CharacterBaseCharacteristicPtr pushDamageReduction;
	CharacterBaseCharacteristicPtr criticalDamageReduction;
	CharacterBaseCharacteristicPtr pvpNeutralElementResistPercent;
	CharacterBaseCharacteristicPtr pvpEarthElementResistPercent;
	CharacterBaseCharacteristicPtr pvpWaterElementResistPercent;
	CharacterBaseCharacteristicPtr pvpAirElementResistPercent;
	CharacterBaseCharacteristicPtr pvpFireElementResistPercent;
	CharacterBaseCharacteristicPtr pvpNeutralElementReduction;
	CharacterBaseCharacteristicPtr pvpEarthElementReduction;
	CharacterBaseCharacteristicPtr pvpWaterElementReduction;
	CharacterBaseCharacteristicPtr pvpAirElementReduction;
	CharacterBaseCharacteristicPtr pvpFireElementReduction;
	std::vector<CharacterSpellModificationPtr> spellModifications;

	uint16 GetProtocol() const
	{ return CHARACTER_CHARACTERISTICS_INFORMATIONS; }

	CharacterCharacteristicsInformations()
	{
	}

	CharacterCharacteristicsInformations(int64 experience, int64 experienceLevelFloor, int64 experienceNextLevelFloor, int kamas, int statsPoints, int spellsPoints, ActorExtendedAlignmentInformations* alignmentInfos, int lifePoints, int maxLifePoints, int16 energyPoints, int16 maxEnergyPoints, int16 actionPointsCurrent, int16 movementPointsCurrent, CharacterBaseCharacteristic* initiative, CharacterBaseCharacteristic* prospecting, CharacterBaseCharacteristic* actionPoints, CharacterBaseCharacteristic* movementPoints, CharacterBaseCharacteristic* strength, CharacterBaseCharacteristic* vitality, CharacterBaseCharacteristic* wisdom, CharacterBaseCharacteristic* chance, CharacterBaseCharacteristic* agility, CharacterBaseCharacteristic* intelligence, CharacterBaseCharacteristic* range, CharacterBaseCharacteristic* summonableCreaturesBoost, CharacterBaseCharacteristic* reflect, CharacterBaseCharacteristic* criticalHit, int16 criticalHitWeapon, CharacterBaseCharacteristic* criticalMiss, CharacterBaseCharacteristic* healBonus, CharacterBaseCharacteristic* allDamagesBonus, CharacterBaseCharacteristic* weaponDamagesBonusPercent, CharacterBaseCharacteristic* damagesBonusPercent, CharacterBaseCharacteristic* trapBonus, CharacterBaseCharacteristic* trapBonusPercent, CharacterBaseCharacteristic* permanentDamagePercent, CharacterBaseCharacteristic* tackleBlock, CharacterBaseCharacteristic* tackleEvade, CharacterBaseCharacteristic* PAAttack, CharacterBaseCharacteristic* PMAttack, CharacterBaseCharacteristic* pushDamageBonus, CharacterBaseCharacteristic* criticalDamageBonus, CharacterBaseCharacteristic* neutralDamageBonus, CharacterBaseCharacteristic* earthDamageBonus, CharacterBaseCharacteristic* waterDamageBonus, CharacterBaseCharacteristic* airDamageBonus, CharacterBaseCharacteristic* fireDamageBonus, CharacterBaseCharacteristic* dodgePALostProbability, CharacterBaseCharacteristic* dodgePMLostProbability, CharacterBaseCharacteristic* neutralElementResistPercent, CharacterBaseCharacteristic* earthElementResistPercent, CharacterBaseCharacteristic* waterElementResistPercent, CharacterBaseCharacteristic* airElementResistPercent, CharacterBaseCharacteristic* fireElementResistPercent, CharacterBaseCharacteristic* neutralElementReduction, CharacterBaseCharacteristic* earthElementReduction, CharacterBaseCharacteristic* waterElementReduction, CharacterBaseCharacteristic* airElementReduction, CharacterBaseCharacteristic* fireElementReduction, CharacterBaseCharacteristic* pushDamageReduction, CharacterBaseCharacteristic* criticalDamageReduction, CharacterBaseCharacteristic* pvpNeutralElementResistPercent, CharacterBaseCharacteristic* pvpEarthElementResistPercent, CharacterBaseCharacteristic* pvpWaterElementResistPercent, CharacterBaseCharacteristic* pvpAirElementResistPercent, CharacterBaseCharacteristic* pvpFireElementResistPercent, CharacterBaseCharacteristic* pvpNeutralElementReduction, CharacterBaseCharacteristic* pvpEarthElementReduction, CharacterBaseCharacteristic* pvpWaterElementReduction, CharacterBaseCharacteristic* pvpAirElementReduction, CharacterBaseCharacteristic* pvpFireElementReduction, std::vector<CharacterSpellModificationPtr>& spellModifications) : experience(experience), experienceLevelFloor(experienceLevelFloor), experienceNextLevelFloor(experienceNextLevelFloor), kamas(kamas), statsPoints(statsPoints), spellsPoints(spellsPoints), alignmentInfos(alignmentInfos), lifePoints(lifePoints), maxLifePoints(maxLifePoints), energyPoints(energyPoints), maxEnergyPoints(maxEnergyPoints), actionPointsCurrent(actionPointsCurrent), movementPointsCurrent(movementPointsCurrent), initiative(initiative), prospecting(prospecting), actionPoints(actionPoints), movementPoints(movementPoints), strength(strength), vitality(vitality), wisdom(wisdom), chance(chance), agility(agility), intelligence(intelligence), range(range), summonableCreaturesBoost(summonableCreaturesBoost), reflect(reflect), criticalHit(criticalHit), criticalHitWeapon(criticalHitWeapon), criticalMiss(criticalMiss), healBonus(healBonus), allDamagesBonus(allDamagesBonus), weaponDamagesBonusPercent(weaponDamagesBonusPercent), damagesBonusPercent(damagesBonusPercent), trapBonus(trapBonus), trapBonusPercent(trapBonusPercent), permanentDamagePercent(permanentDamagePercent), tackleBlock(tackleBlock), tackleEvade(tackleEvade), PAAttack(PAAttack), PMAttack(PMAttack), pushDamageBonus(pushDamageBonus), criticalDamageBonus(criticalDamageBonus), neutralDamageBonus(neutralDamageBonus), earthDamageBonus(earthDamageBonus), waterDamageBonus(waterDamageBonus), airDamageBonus(airDamageBonus), fireDamageBonus(fireDamageBonus), dodgePALostProbability(dodgePALostProbability), dodgePMLostProbability(dodgePMLostProbability), neutralElementResistPercent(neutralElementResistPercent), earthElementResistPercent(earthElementResistPercent), waterElementResistPercent(waterElementResistPercent), airElementResistPercent(airElementResistPercent), fireElementResistPercent(fireElementResistPercent), neutralElementReduction(neutralElementReduction), earthElementReduction(earthElementReduction), waterElementReduction(waterElementReduction), airElementReduction(airElementReduction), fireElementReduction(fireElementReduction), pushDamageReduction(pushDamageReduction), criticalDamageReduction(criticalDamageReduction), pvpNeutralElementResistPercent(pvpNeutralElementResistPercent), pvpEarthElementResistPercent(pvpEarthElementResistPercent), pvpWaterElementResistPercent(pvpWaterElementResistPercent), pvpAirElementResistPercent(pvpAirElementResistPercent), pvpFireElementResistPercent(pvpFireElementResistPercent), pvpNeutralElementReduction(pvpNeutralElementReduction), pvpEarthElementReduction(pvpEarthElementReduction), pvpWaterElementReduction(pvpWaterElementReduction), pvpAirElementReduction(pvpAirElementReduction), pvpFireElementReduction(pvpFireElementReduction), spellModifications(spellModifications)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<experience<<experienceLevelFloor<<experienceNextLevelFloor<<kamas<<statsPoints<<spellsPoints;
		alignmentInfos->Serialize(data);
		data<<lifePoints<<maxLifePoints<<energyPoints<<maxEnergyPoints<<actionPointsCurrent<<movementPointsCurrent;
		initiative->Serialize(data);
		prospecting->Serialize(data);
		actionPoints->Serialize(data);
		movementPoints->Serialize(data);
		strength->Serialize(data);
		vitality->Serialize(data);
		wisdom->Serialize(data);
		chance->Serialize(data);
		agility->Serialize(data);
		intelligence->Serialize(data);
		range->Serialize(data);
		summonableCreaturesBoost->Serialize(data);
		reflect->Serialize(data);
		criticalHit->Serialize(data);
		data<<criticalHitWeapon;
		criticalMiss->Serialize(data);
		healBonus->Serialize(data);
		allDamagesBonus->Serialize(data);
		weaponDamagesBonusPercent->Serialize(data);
		damagesBonusPercent->Serialize(data);
		trapBonus->Serialize(data);
		trapBonusPercent->Serialize(data);
		permanentDamagePercent->Serialize(data);
		tackleBlock->Serialize(data);
		tackleEvade->Serialize(data);
		PAAttack->Serialize(data);
		PMAttack->Serialize(data);
		pushDamageBonus->Serialize(data);
		criticalDamageBonus->Serialize(data);
		neutralDamageBonus->Serialize(data);
		earthDamageBonus->Serialize(data);
		waterDamageBonus->Serialize(data);
		airDamageBonus->Serialize(data);
		fireDamageBonus->Serialize(data);
		dodgePALostProbability->Serialize(data);
		dodgePMLostProbability->Serialize(data);
		neutralElementResistPercent->Serialize(data);
		earthElementResistPercent->Serialize(data);
		waterElementResistPercent->Serialize(data);
		airElementResistPercent->Serialize(data);
		fireElementResistPercent->Serialize(data);
		neutralElementReduction->Serialize(data);
		earthElementReduction->Serialize(data);
		waterElementReduction->Serialize(data);
		airElementReduction->Serialize(data);
		fireElementReduction->Serialize(data);
		pushDamageReduction->Serialize(data);
		criticalDamageReduction->Serialize(data);
		pvpNeutralElementResistPercent->Serialize(data);
		pvpEarthElementResistPercent->Serialize(data);
		pvpWaterElementResistPercent->Serialize(data);
		pvpAirElementResistPercent->Serialize(data);
		pvpFireElementResistPercent->Serialize(data);
		pvpNeutralElementReduction->Serialize(data);
		pvpEarthElementReduction->Serialize(data);
		pvpWaterElementReduction->Serialize(data);
		pvpAirElementReduction->Serialize(data);
		pvpFireElementReduction->Serialize(data);
		uint16 size = spellModifications.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			spellModifications[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>experience>>experienceLevelFloor>>experienceNextLevelFloor>>kamas>>statsPoints>>spellsPoints;
		alignmentInfos.reset(new ActorExtendedAlignmentInformations);
		alignmentInfos->Deserialize(data);
		data>>lifePoints>>maxLifePoints>>energyPoints>>maxEnergyPoints>>actionPointsCurrent>>movementPointsCurrent;
		initiative.reset(new CharacterBaseCharacteristic);
		initiative->Deserialize(data);
		prospecting.reset(new CharacterBaseCharacteristic);
		prospecting->Deserialize(data);
		actionPoints.reset(new CharacterBaseCharacteristic);
		actionPoints->Deserialize(data);
		movementPoints.reset(new CharacterBaseCharacteristic);
		movementPoints->Deserialize(data);
		strength.reset(new CharacterBaseCharacteristic);
		strength->Deserialize(data);
		vitality.reset(new CharacterBaseCharacteristic);
		vitality->Deserialize(data);
		wisdom.reset(new CharacterBaseCharacteristic);
		wisdom->Deserialize(data);
		chance.reset(new CharacterBaseCharacteristic);
		chance->Deserialize(data);
		agility.reset(new CharacterBaseCharacteristic);
		agility->Deserialize(data);
		intelligence.reset(new CharacterBaseCharacteristic);
		intelligence->Deserialize(data);
		range.reset(new CharacterBaseCharacteristic);
		range->Deserialize(data);
		summonableCreaturesBoost.reset(new CharacterBaseCharacteristic);
		summonableCreaturesBoost->Deserialize(data);
		reflect.reset(new CharacterBaseCharacteristic);
		reflect->Deserialize(data);
		criticalHit.reset(new CharacterBaseCharacteristic);
		criticalHit->Deserialize(data);
		data>>criticalHitWeapon;
		criticalMiss.reset(new CharacterBaseCharacteristic);
		criticalMiss->Deserialize(data);
		healBonus.reset(new CharacterBaseCharacteristic);
		healBonus->Deserialize(data);
		allDamagesBonus.reset(new CharacterBaseCharacteristic);
		allDamagesBonus->Deserialize(data);
		weaponDamagesBonusPercent.reset(new CharacterBaseCharacteristic);
		weaponDamagesBonusPercent->Deserialize(data);
		damagesBonusPercent.reset(new CharacterBaseCharacteristic);
		damagesBonusPercent->Deserialize(data);
		trapBonus.reset(new CharacterBaseCharacteristic);
		trapBonus->Deserialize(data);
		trapBonusPercent.reset(new CharacterBaseCharacteristic);
		trapBonusPercent->Deserialize(data);
		permanentDamagePercent.reset(new CharacterBaseCharacteristic);
		permanentDamagePercent->Deserialize(data);
		tackleBlock.reset(new CharacterBaseCharacteristic);
		tackleBlock->Deserialize(data);
		tackleEvade.reset(new CharacterBaseCharacteristic);
		tackleEvade->Deserialize(data);
		PAAttack.reset(new CharacterBaseCharacteristic);
		PAAttack->Deserialize(data);
		PMAttack.reset(new CharacterBaseCharacteristic);
		PMAttack->Deserialize(data);
		pushDamageBonus.reset(new CharacterBaseCharacteristic);
		pushDamageBonus->Deserialize(data);
		criticalDamageBonus.reset(new CharacterBaseCharacteristic);
		criticalDamageBonus->Deserialize(data);
		neutralDamageBonus.reset(new CharacterBaseCharacteristic);
		neutralDamageBonus->Deserialize(data);
		earthDamageBonus.reset(new CharacterBaseCharacteristic);
		earthDamageBonus->Deserialize(data);
		waterDamageBonus.reset(new CharacterBaseCharacteristic);
		waterDamageBonus->Deserialize(data);
		airDamageBonus.reset(new CharacterBaseCharacteristic);
		airDamageBonus->Deserialize(data);
		fireDamageBonus.reset(new CharacterBaseCharacteristic);
		fireDamageBonus->Deserialize(data);
		dodgePALostProbability.reset(new CharacterBaseCharacteristic);
		dodgePALostProbability->Deserialize(data);
		dodgePMLostProbability.reset(new CharacterBaseCharacteristic);
		dodgePMLostProbability->Deserialize(data);
		neutralElementResistPercent.reset(new CharacterBaseCharacteristic);
		neutralElementResistPercent->Deserialize(data);
		earthElementResistPercent.reset(new CharacterBaseCharacteristic);
		earthElementResistPercent->Deserialize(data);
		waterElementResistPercent.reset(new CharacterBaseCharacteristic);
		waterElementResistPercent->Deserialize(data);
		airElementResistPercent.reset(new CharacterBaseCharacteristic);
		airElementResistPercent->Deserialize(data);
		fireElementResistPercent.reset(new CharacterBaseCharacteristic);
		fireElementResistPercent->Deserialize(data);
		neutralElementReduction.reset(new CharacterBaseCharacteristic);
		neutralElementReduction->Deserialize(data);
		earthElementReduction.reset(new CharacterBaseCharacteristic);
		earthElementReduction->Deserialize(data);
		waterElementReduction.reset(new CharacterBaseCharacteristic);
		waterElementReduction->Deserialize(data);
		airElementReduction.reset(new CharacterBaseCharacteristic);
		airElementReduction->Deserialize(data);
		fireElementReduction.reset(new CharacterBaseCharacteristic);
		fireElementReduction->Deserialize(data);
		pushDamageReduction.reset(new CharacterBaseCharacteristic);
		pushDamageReduction->Deserialize(data);
		criticalDamageReduction.reset(new CharacterBaseCharacteristic);
		criticalDamageReduction->Deserialize(data);
		pvpNeutralElementResistPercent.reset(new CharacterBaseCharacteristic);
		pvpNeutralElementResistPercent->Deserialize(data);
		pvpEarthElementResistPercent.reset(new CharacterBaseCharacteristic);
		pvpEarthElementResistPercent->Deserialize(data);
		pvpWaterElementResistPercent.reset(new CharacterBaseCharacteristic);
		pvpWaterElementResistPercent->Deserialize(data);
		pvpAirElementResistPercent.reset(new CharacterBaseCharacteristic);
		pvpAirElementResistPercent->Deserialize(data);
		pvpFireElementResistPercent.reset(new CharacterBaseCharacteristic);
		pvpFireElementResistPercent->Deserialize(data);
		pvpNeutralElementReduction.reset(new CharacterBaseCharacteristic);
		pvpNeutralElementReduction->Deserialize(data);
		pvpEarthElementReduction.reset(new CharacterBaseCharacteristic);
		pvpEarthElementReduction->Deserialize(data);
		pvpWaterElementReduction.reset(new CharacterBaseCharacteristic);
		pvpWaterElementReduction->Deserialize(data);
		pvpAirElementReduction.reset(new CharacterBaseCharacteristic);
		pvpAirElementReduction->Deserialize(data);
		pvpFireElementReduction.reset(new CharacterBaseCharacteristic);
		pvpFireElementReduction->Deserialize(data);
		spellModifications.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterSpellModificationPtr model(new CharacterSpellModification);
			model->Deserialize(data);
			spellModifications.push_back(model);
		}
	}
};

typedef boost::shared_ptr<CharacterCharacteristicsInformations> CharacterCharacteristicsInformationsPtr;

#endif