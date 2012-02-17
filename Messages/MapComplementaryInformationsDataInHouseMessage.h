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

#ifndef __MAP_COMPLEMENTARY_INFORMATIONS_DATA_IN_HOUSE_MESSAGE__
#define __MAP_COMPLEMENTARY_INFORMATIONS_DATA_IN_HOUSE_MESSAGE__

class MapComplementaryInformationsDataInHouseMessage : public MapComplementaryInformationsDataMessage
{
public:
	HouseInformationsInsidePtr currentHouse;

	uint16 GetOpcode() const
	{ return SMSG_MAP_COMPLEMENTARY_INFORMATIONS_DATA_IN_HOUSE; }

	MapComplementaryInformationsDataInHouseMessage()
	{
	}

	MapComplementaryInformationsDataInHouseMessage(int16 subAreaId, int mapId, int8 subareaAlignmentSide, std::vector<HouseInformationsPtr>& houses, std::vector<GameRolePlayActorInformationsPtr>& actors, std::vector<InteractiveElementPtr>& interactiveElements, std::vector<StatedElementPtr>& statedElements, std::vector<MapObstaclePtr>& obstacles, std::vector<FightCommonInformationsPtr>& fights, HouseInformationsInside* currentHouse) : MapComplementaryInformationsDataMessage(subAreaId, mapId, subareaAlignmentSide, houses, actors, interactiveElements, statedElements, obstacles, fights), currentHouse(currentHouse)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		MapComplementaryInformationsDataMessage::Serialize(data);
		currentHouse->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		MapComplementaryInformationsDataMessage::Deserialize(data);
		currentHouse.reset(new HouseInformationsInside);
		currentHouse->Deserialize(data);
	}
};

#endif