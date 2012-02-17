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

#ifndef __JOB_CRAFTER_DIRECTORY_ENTRY_PLAYER_INFO__
#define __JOB_CRAFTER_DIRECTORY_ENTRY_PLAYER_INFO__

class JobCrafterDirectoryEntryPlayerInfo : public DofusModel
{
public:
	int playerId;
	std::string playerName;
	int8 alignmentSide;
	int8 breed;
	bool sex;
	bool isInWorkshop;
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;

	uint16 GetProtocol() const
	{ return JOB_CRAFTER_DIRECTORY_ENTRY_PLAYER_INFO; }

	JobCrafterDirectoryEntryPlayerInfo()
	{
	}

	JobCrafterDirectoryEntryPlayerInfo(int playerId, std::string playerName, int8 alignmentSide, int8 breed, bool sex, bool isInWorkshop, int16 worldX, int16 worldY, int mapId, int16 subAreaId) : playerId(playerId), playerName(playerName), alignmentSide(alignmentSide), breed(breed), sex(sex), isInWorkshop(isInWorkshop), worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<playerId<<playerName<<alignmentSide<<breed<<sex<<isInWorkshop<<worldX<<worldY<<mapId<<subAreaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>playerId>>playerName>>alignmentSide>>breed>>sex>>isInWorkshop>>worldX>>worldY>>mapId>>subAreaId;
	}
};

typedef boost::shared_ptr<JobCrafterDirectoryEntryPlayerInfo> JobCrafterDirectoryEntryPlayerInfoPtr;

#endif