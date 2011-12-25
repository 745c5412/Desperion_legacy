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

#ifndef __MAP_OBSTACLE_UPDATE_MESSAGE__
#define __MAP_OBSTACLE_UPDATE_MESSAGE__

class MapObstacleUpdateMessage : public DofusMessage
{
public:
	std::vector<MapObstaclePtr> obstacles;

	uint16 GetOpcode() const
	{ return SMSG_MAP_OBSTACLE_UPDATE; }

	MapObstacleUpdateMessage()
	{
	}

	MapObstacleUpdateMessage(std::vector<MapObstaclePtr>& obstacles) : obstacles(obstacles)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = obstacles.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			obstacles[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		obstacles.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MapObstaclePtr model(new MapObstacle);
			model->Deserialize(data);
			obstacles.push_back(model);
		}
	}
};

#endif