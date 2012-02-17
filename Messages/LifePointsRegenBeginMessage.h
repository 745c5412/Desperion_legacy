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

#ifndef __LIFE_POINTS_REGEN_BEGIN_MESSAGE__
#define __LIFE_POINTS_REGEN_BEGIN_MESSAGE__

class LifePointsRegenBeginMessage : public DofusMessage
{
public:
	uint8 regenRate;

	uint16 GetOpcode() const
	{ return SMSG_LIFE_POINTS_REGEN_BEGIN; }

	LifePointsRegenBeginMessage()
	{
	}

	LifePointsRegenBeginMessage(uint8 regenRate) : regenRate(regenRate)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<regenRate;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>regenRate;
	}
};

#endif