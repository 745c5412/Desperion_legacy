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

#ifndef __MAP_COORDINATES_EXTENDED__
#define __MAP_COORDINATES_EXTENDED__

class MapCoordinatesExtended : public MapCoordinates
{
public:
	int mapId;
	int16 subAreaId;

	uint16 GetProtocol() const
	{ return MAP_COORDINATES_EXTENDED; }

	MapCoordinatesExtended()
	{
	}

	MapCoordinatesExtended(int16 worldX, int16 worldY, int mapId, int16 subAreaId) : MapCoordinates(worldX, worldY), mapId(mapId), subAreaId(subAreaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		MapCoordinates::Serialize(data);
		data<<mapId<<subAreaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		MapCoordinates::Deserialize(data);
		data>>mapId>>subAreaId;
	}
};

typedef boost::shared_ptr<MapCoordinatesExtended> MapCoordinatesExtendedPtr;

#endif