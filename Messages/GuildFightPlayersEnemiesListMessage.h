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

#ifndef __GUILD_FIGHT_PLAYERS_ENEMIES_LIST_MESSAGE__
#define __GUILD_FIGHT_PLAYERS_ENEMIES_LIST_MESSAGE__

class GuildFightPlayersEnemiesListMessage : public DofusMessage
{
public:
	int64 fightId;
	std::vector<CharacterMinimalPlusLookInformationsPtr> playerInfo;

	uint16 GetOpcode() const
	{ return SMSG_GUILD_FIGHT_PLAYERS_ENEMIES_LIST; }

	GuildFightPlayersEnemiesListMessage()
	{
	}

	GuildFightPlayersEnemiesListMessage(int64 fightId, std::vector<CharacterMinimalPlusLookInformationsPtr>& playerInfo) : fightId(fightId), playerInfo(playerInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<fightId;
		uint16 size = playerInfo.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			playerInfo[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightId;
		playerInfo.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookInformationsPtr model(new CharacterMinimalPlusLookInformations);
			model->Deserialize(data);
			playerInfo.push_back(model);
		}
	}
};

#endif