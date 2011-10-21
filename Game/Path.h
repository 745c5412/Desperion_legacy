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

#ifndef __PATH__
#define __PATH__

namespace Desperion
{
	struct MapPoint
	{
		int x;
		int y;
	};

#define VECTOR_RIGHT_X 1
#define VECTOR_RIGHT_Y 1

#define VECTOR_DOWN_RIGHT_X 1
#define VECTOR_DOWN_RIGHT_Y 0

#define VECTOR_DOWN_X 1
#define VECTOR_DOWN_Y -1

#define VECTOR_DOWN_LEFT_X 0
#define VECTOR_DOWN_LEFT_Y -1

#define VECTOR_LEFT_X -1
#define VECTOR_LEFT_Y -1

#define VECTOR_UP_LEFT_X -1
#define VECTOR_UP_LEFT_Y 0

#define VECTOR_UP_X -1
#define VECTOR_UP_Y 1

#define VECTOR_UP_RIGHT_X 0
#define VECTOR_UP_RIGHT_Y 1

	int8 OrientationTo(MapPoint&, MapPoint&);
}

#endif