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

#ifndef __MAP_COMPLEMENTARY_INFORMATIONS_DATA_MESSAGE__
#define __MAP_COMPLEMENTARY_INFORMATIONS_DATA_MESSAGE__

class MapComplementaryInformationsDataMessage : public DofusMessage
{
public:
	int16 subAreaId;
	int mapId;
	int8 subareaAlignmentSide;
	std::vector<HouseInformationsPtr> houses;
	std::vector<GameRolePlayActorInformationsPtr> actors;
	std::vector<InteractiveElementPtr> interactiveElements;
	std::vector<StatedElementPtr> statedElements;
	std::vector<MapObstaclePtr> obstacles;
	std::vector<FightCommonInformationsPtr> fights;

	uint16 GetOpcode() const
	{ return SMSG_MAP_COMPLEMENTARY_INFORMATIONS_DATA; }

	MapComplementaryInformationsDataMessage()
	{
	}

	MapComplementaryInformationsDataMessage(int16 subAreaId, int mapId, int8 subareaAlignmentSide, std::vector<HouseInformationsPtr>& houses, std::vector<GameRolePlayActorInformationsPtr>& actors, std::vector<InteractiveElementPtr>& interactiveElements, std::vector<StatedElementPtr>& statedElements, std::vector<MapObstaclePtr>& obstacles, std::vector<FightCommonInformationsPtr>& fights) : subAreaId(subAreaId), mapId(mapId), subareaAlignmentSide(subareaAlignmentSide), houses(houses), actors(actors), interactiveElements(interactiveElements), statedElements(statedElements), obstacles(obstacles), fights(fights)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<subAreaId<<mapId<<subareaAlignmentSide;
		uint16 size = houses.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<houses[a]->GetProtocol();
			houses[a]->Serialize(data);
		}
		size = actors.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<actors[a]->GetProtocol();
			actors[a]->Serialize(data);
		}
		size = interactiveElements.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			interactiveElements[a]->Serialize(data);
		size = statedElements.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			statedElements[a]->Serialize(data);
		size = obstacles.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			obstacles[a]->Serialize(data);
		size = fights.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			fights[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>subAreaId>>mapId>>subareaAlignmentSide;
		houses.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			HouseInformationsPtr model(Desperion::ProtocolTypeManager::GetHouseInformations(protocol));
			model->Deserialize(data);
			houses.push_back(model);
		}
		actors.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			GameRolePlayActorInformationsPtr model(Desperion::ProtocolTypeManager::GetGameRolePlayActorInformations(protocol));
			model->Deserialize(data);
			actors.push_back(model);
		}
		interactiveElements.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			InteractiveElementPtr model(new InteractiveElement);
			model->Deserialize(data);
			interactiveElements.push_back(model);
		}
		statedElements.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			StatedElementPtr model(new StatedElement);
			model->Deserialize(data);
			statedElements.push_back(model);
		}
		obstacles.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MapObstaclePtr model(new MapObstacle);
			model->Deserialize(data);
			obstacles.push_back(model);
		}
		fights.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			FightCommonInformationsPtr model(new FightCommonInformations);
			model->Deserialize(data);
			fights.push_back(model);
		}
	}
};

#endif