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

#ifndef __LIFE_POINTS_REGEN_END_MESSAGE__
#define __LIFE_POINTS_REGEN_END_MESSAGE__

class LifePointsRegenEndMessage : public UpdateLifePointsMessage
{
public:
	int lifePointsGained;

	uint16 GetOpcode() const
	{ return SMSG_LIFE_POINTS_REGEN_END; }

	LifePointsRegenEndMessage()
	{
	}

	LifePointsRegenEndMessage(int lifePoints, int maxLifePoints, int lifePointsGained) : UpdateLifePointsMessage(lifePoints, maxLifePoints), lifePointsGained(lifePointsGained)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		UpdateLifePointsMessage::Serialize(data);
		data<<lifePointsGained;
	}

	void Deserialize(ByteBuffer& data)
	{
		UpdateLifePointsMessage::Deserialize(data);
		data>>lifePointsGained;
	}
};

#endif