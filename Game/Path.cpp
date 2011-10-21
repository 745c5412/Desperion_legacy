/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#include "StdAfx.h"

namespace Desperion
{
	int8 OrientationTo(MapPoint& p1, MapPoint& p2)
	{
		int x = p1.x > p2.x ? (1) : (p1.x < p2.x ? (-1) : (0));
		int y = p1.y > p2.y ? (1) : (p1.y < p2.y ? (-1) : (0));
		int8 dir = 0;
		if (x == VECTOR_RIGHT_X && y == VECTOR_RIGHT_X)
            dir = DIRECTION_EAST;
        else if (x == VECTOR_DOWN_RIGHT_X && y == VECTOR_DOWN_RIGHT_Y)
            dir = DIRECTION_SOUTH_EAST;
        else if (x == VECTOR_DOWN_X && y == VECTOR_DOWN_Y)
            dir = DIRECTION_SOUTH;
        else if (x == VECTOR_DOWN_LEFT_X && y == VECTOR_DOWN_LEFT_Y)
            dir = DIRECTION_SOUTH_WEST;
        else if (x == VECTOR_LEFT_X && y == VECTOR_LEFT_Y)
            dir = DIRECTION_WEST;
        else if (x == VECTOR_UP_LEFT_X && y == VECTOR_UP_LEFT_Y)
            dir = DIRECTION_NORTH_WEST;
        else if (x == VECTOR_UP_X && y == VECTOR_UP_Y)
            dir = DIRECTION_NORTH;
        else if (x == VECTOR_UP_RIGHT_X && y == VECTOR_UP_RIGHT_Y)
            dir = DIRECTION_NORTH_EAST;
		return dir;
	}
}