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

#ifndef __DUNGEON_PARTY_FINDER_PLAYER__
#define __DUNGEON_PARTY_FINDER_PLAYER__

class DungeonPartyFinderPlayer : public DofusModel
{
public:
	int playerId;
	std::string playerName;
	int8 breed;
	bool sex;
	int16 level;

	uint16 GetProtocol() const
	{ return DUNGEON_PARTY_FINDER_PLAYER; }

	DungeonPartyFinderPlayer()
	{
	}

	DungeonPartyFinderPlayer(int playerId, std::string playerName, int8 breed, bool sex, int16 level) : playerId(playerId), playerName(playerName), breed(breed), sex(sex), level(level)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<playerId<<playerName<<breed<<sex<<level;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>playerId>>playerName>>breed>>sex>>level;
	}
};

typedef boost::shared_ptr<DungeonPartyFinderPlayer> DungeonPartyFinderPlayerPtr;

#endif