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

#ifndef __GAME_ROLE_PLAY_ARENA_UPDATE_PLAYER_INFOS_MESSAGE__
#define __GAME_ROLE_PLAY_ARENA_UPDATE_PLAYER_INFOS_MESSAGE__

class GameRolePlayArenaUpdatePlayerInfosMessage : public DofusMessage
{
public:
	int16 rank;
	int16 bestDailyRank;
	int16 bestRank;
	int16 victoryCount;
	int16 arenaFightcount;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ROLE_PLAY_ARENA_UPDATE_PLAYER_INFOS; }

	GameRolePlayArenaUpdatePlayerInfosMessage()
	{
	}

	GameRolePlayArenaUpdatePlayerInfosMessage(int16 rank, int16 bestDailyRank, int16 bestRank, int16 victoryCount, int16 arenaFightcount) : rank(rank), bestDailyRank(bestDailyRank), bestRank(bestRank), victoryCount(victoryCount), arenaFightcount(arenaFightcount)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<rank<<bestDailyRank<<bestRank<<victoryCount<<arenaFightcount;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>rank>>bestDailyRank>>bestRank>>victoryCount>>arenaFightcount;
	}
};

#endif