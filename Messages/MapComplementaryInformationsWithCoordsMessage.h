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

#ifndef __MAP_COMPLEMENTARY_INFORMATIONS_WITH_COORDS_MESSAGE__
#define __MAP_COMPLEMENTARY_INFORMATIONS_WITH_COORDS_MESSAGE__

class MapComplementaryInformationsWithCoordsMessage : public MapComplementaryInformationsDataMessage
{
public:
	int16 worldX;
	int16 worldY;

	uint16 GetOpcode() const
	{ return SMSG_MAP_COMPLEMENTARY_INFORMATIONS_WITH_COORDS; }

	MapComplementaryInformationsWithCoordsMessage()
	{
	}

	MapComplementaryInformationsWithCoordsMessage(int16 subAreaId, int mapId, int8 subareaAlignmentSide, std::vector<HouseInformationsPtr>& houses, std::vector<GameRolePlayActorInformationsPtr>& actors, std::vector<InteractiveElementPtr>& interactiveElements, std::vector<StatedElementPtr>& statedElements, std::vector<MapObstaclePtr>& obstacles, std::vector<FightCommonInformationsPtr>& fights, int16 worldX, int16 worldY) : MapComplementaryInformationsDataMessage(subAreaId, mapId, subareaAlignmentSide, houses, actors, interactiveElements, statedElements, obstacles, fights), worldX(worldX), worldY(worldY)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		MapComplementaryInformationsDataMessage::Serialize(data);
		data<<worldX<<worldY;
	}

	void Deserialize(ByteBuffer& data)
	{
		MapComplementaryInformationsDataMessage::Deserialize(data);
		data>>worldX>>worldY;
	}
};

#endif