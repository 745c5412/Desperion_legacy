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

#ifndef __COMPASS_UPDATE_MESSAGE__
#define __COMPASS_UPDATE_MESSAGE__

class CompassUpdateMessage : public DofusMessage
{
public:
	int8 type;
	int16 worldX;
	int16 worldY;

	uint16 GetOpcode() const
	{ return SMSG_COMPASS_UPDATE; }

	CompassUpdateMessage()
	{
	}

	CompassUpdateMessage(int8 type, int16 worldX, int16 worldY) : type(type), worldX(worldX), worldY(worldY)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<type<<worldX<<worldY;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>type>>worldX>>worldY;
	}
};

#endif