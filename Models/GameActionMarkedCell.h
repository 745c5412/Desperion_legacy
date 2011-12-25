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

#ifndef __GAME_ACTION_MARKED_CELL__
#define __GAME_ACTION_MARKED_CELL__

class GameActionMarkedCell : public DofusModel
{
public:
	int16 cellId;
	int8 zoneSize;
	int cellColor;
	int8 cellsType;

	uint16 GetProtocol() const
	{ return GAME_ACTION_MARKED_CELL; }

	GameActionMarkedCell()
	{
	}

	GameActionMarkedCell(int16 cellId, int8 zoneSize, int cellColor, int8 cellsType) : cellId(cellId), zoneSize(zoneSize), cellColor(cellColor), cellsType(cellsType)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<cellId<<zoneSize<<cellColor<<cellsType;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>cellId>>zoneSize>>cellColor>>cellsType;
	}
};

typedef boost::shared_ptr<GameActionMarkedCell> GameActionMarkedCellPtr;

#endif