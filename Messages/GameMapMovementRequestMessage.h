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

#ifndef __GAME_MAP_MOVEMENT_REQUEST_MESSAGE__
#define __GAME_MAP_MOVEMENT_REQUEST_MESSAGE__

class GameMapMovementRequestMessage : public DofusMessage
{
public:
	std::vector<int16> keyMovements;
	int mapId;

	virtual uint16 GetOpcode() const
	{ return CMSG_GAME_MAP_MOVEMENT_REQUEST; }

	GameMapMovementRequestMessage()
	{
	}

	GameMapMovementRequestMessage(std::vector<int16>& keyMovements, int mapId) : keyMovements(keyMovements),
		mapId(mapId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = keyMovements.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<keyMovements[a];
		data<<mapId;
	}

	void Deserialize(ByteBuffer& data)
	{
		keyMovements.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 key;
			data>>key;
			keyMovements.push_back(key);
		}
		data>>mapId;
	}
};

#endif