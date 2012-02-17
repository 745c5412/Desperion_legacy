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

#ifndef __MAP_COORDINATES__
#define __MAP_COORDINATES__

class MapCoordinates : public DofusModel
{
public:
	int16 worldX;
	int16 worldY;

	uint16 GetProtocol() const
	{ return MAP_COORDINATES; }

	MapCoordinates()
	{
	}

	MapCoordinates(int16 worldX, int16 worldY) : worldX(worldX), worldY(worldY)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<worldX<<worldY;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>worldX>>worldY;
	}
};

typedef boost::shared_ptr<MapCoordinates> MapCoordinatesPtr;

#endif