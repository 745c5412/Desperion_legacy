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

#ifndef __GAME_FIGHT_MINIMAL_STATS__
#define __GAME_FIGHT_MINIMAL_STATS__

class GameFightMinimalStats : public DofusModel
{
public:
	int lifePoints;
	int maxLifePoints;
	int baseMaxLifePoints;
	int permanentDamagePercent;
	int shieldPoints;
	int16 actionPoints;
	int16 maxActionPoints;
	int16 movementPoints;
	int16 maxMovementPoints;
	int summoner;
	bool summoned;
	int16 neutralElementResistPercent;
	int16 earthElementResistPercent;
	int16 waterElementResistPercent;
	int16 airElementResistPercent;
	int16 fireElementResistPercent;
	int16 dodgePALostProbability;
	int16 dodgePMLostProbability;
	int16 tackleBlock;
	int16 tackleEvade;
	int8 invisibilityState;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_MINIMAL_STATS; }

	GameFightMinimalStats()
	{
	}

	GameFightMinimalStats(int lifePoints, int maxLifePoints, int baseMaxLifePoints, int permanentDamagePercent, int shieldPoints, int16 actionPoints, int16 maxActionPoints, int16 movementPoints, int16 maxMovementPoints, int summoner, bool summoned, int16 neutralElementResistPercent, int16 earthElementResistPercent, int16 waterElementResistPercent, int16 airElementResistPercent, int16 fireElementResistPercent, int16 dodgePALostProbability, int16 dodgePMLostProbability, int16 tackleBlock, int16 tackleEvade, int8 invisibilityState) : lifePoints(lifePoints), maxLifePoints(maxLifePoints), baseMaxLifePoints(baseMaxLifePoints), permanentDamagePercent(permanentDamagePercent), shieldPoints(shieldPoints), actionPoints(actionPoints), maxActionPoints(maxActionPoints), movementPoints(movementPoints), maxMovementPoints(maxMovementPoints), summoner(summoner), summoned(summoned), neutralElementResistPercent(neutralElementResistPercent), earthElementResistPercent(earthElementResistPercent), waterElementResistPercent(waterElementResistPercent), airElementResistPercent(airElementResistPercent), fireElementResistPercent(fireElementResistPercent), dodgePALostProbability(dodgePALostProbability), dodgePMLostProbability(dodgePMLostProbability), tackleBlock(tackleBlock), tackleEvade(tackleEvade), invisibilityState(invisibilityState)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<lifePoints<<maxLifePoints<<baseMaxLifePoints<<permanentDamagePercent<<shieldPoints<<actionPoints<<maxActionPoints<<movementPoints<<maxMovementPoints<<summoner<<summoned<<neutralElementResistPercent<<earthElementResistPercent<<waterElementResistPercent<<airElementResistPercent<<fireElementResistPercent<<dodgePALostProbability<<dodgePMLostProbability<<tackleBlock<<tackleEvade<<invisibilityState;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>lifePoints>>maxLifePoints>>baseMaxLifePoints>>permanentDamagePercent>>shieldPoints>>actionPoints>>maxActionPoints>>movementPoints>>maxMovementPoints>>summoner>>summoned>>neutralElementResistPercent>>earthElementResistPercent>>waterElementResistPercent>>airElementResistPercent>>fireElementResistPercent>>dodgePALostProbability>>dodgePMLostProbability>>tackleBlock>>tackleEvade>>invisibilityState;
	}
};

typedef boost::shared_ptr<GameFightMinimalStats> GameFightMinimalStatsPtr;

#endif