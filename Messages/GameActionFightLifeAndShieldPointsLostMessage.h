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

#ifndef __GAME_ACTION_FIGHT_LIFE_AND_SHIELD_POINTS_LOST_MESSAGE__
#define __GAME_ACTION_FIGHT_LIFE_AND_SHIELD_POINTS_LOST_MESSAGE__

class GameActionFightLifeAndShieldPointsLostMessage : public GameActionFightLifePointsLostMessage
{
public:
	int16 shieldLoss;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ACTION_FIGHT_LIFE_AND_SHIELD_POINTS_LOST; }

	GameActionFightLifeAndShieldPointsLostMessage()
	{
	}

	GameActionFightLifeAndShieldPointsLostMessage(int16 actionId, int sourceId, int targetId, int16 loss, int16 permanentDamages, int16 shieldLoss) : GameActionFightLifePointsLostMessage(actionId, sourceId, targetId, loss, permanentDamages), shieldLoss(shieldLoss)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameActionFightLifePointsLostMessage::Serialize(data);
		data<<shieldLoss;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameActionFightLifePointsLostMessage::Deserialize(data);
		data>>shieldLoss;
	}
};

#endif