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

#ifndef __DUNGEON_PARTY_FINDER_ROOM_CONTENT_MESSAGE__
#define __DUNGEON_PARTY_FINDER_ROOM_CONTENT_MESSAGE__

class DungeonPartyFinderRoomContentMessage : public DofusMessage
{
public:
	int16 dungeonId;
	std::vector<DungeonPartyFinderPlayerPtr> players;

	uint16 GetOpcode() const
	{ return SMSG_DUNGEON_PARTY_FINDER_ROOM_CONTENT; }

	DungeonPartyFinderRoomContentMessage()
	{
	}

	DungeonPartyFinderRoomContentMessage(int16 dungeonId, std::vector<DungeonPartyFinderPlayerPtr>& players) : dungeonId(dungeonId), players(players)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<dungeonId;
		uint16 size = players.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			players[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>dungeonId;
		players.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			DungeonPartyFinderPlayerPtr model(new DungeonPartyFinderPlayer);
			model->Deserialize(data);
			players.push_back(model);
		}
	}
};

#endif