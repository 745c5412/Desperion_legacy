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

#ifndef __CHALLENGE_DUNGEON_STACKED_BONUS_MESSAGE__
#define __CHALLENGE_DUNGEON_STACKED_BONUS_MESSAGE__

class ChallengeDungeonStackedBonusMessage : public DofusMessage
{
public:
	int dungeonId;
	int xpBonus;
	int dropBonus;

	uint16 GetOpcode() const
	{ return SMSG_CHALLENGE_DUNGEON_STACKED_BONUS; }

	ChallengeDungeonStackedBonusMessage()
	{
	}

	ChallengeDungeonStackedBonusMessage(int dungeonId, int xpBonus, int dropBonus) : dungeonId(dungeonId), xpBonus(xpBonus), dropBonus(dropBonus)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<dungeonId<<xpBonus<<dropBonus;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>dungeonId>>xpBonus>>dropBonus;
	}
};

#endif