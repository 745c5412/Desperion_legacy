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

#ifndef __GAME_MAP_MOVEMENT_MESSAGE__
#define __GAME_MAP_MOVEMENT_MESSAGE__

class GameMapMovementMessage : public DofusMessage
{
public:
	std::vector<int16> keyMovements;
	int guid;

	virtual uint16 GetOpcode() const
	{ return SMSG_GAME_MAP_MOVEMENT; }

	GameMapMovementMessage()
	{
	}

	GameMapMovementMessage(std::vector<int16>& keyMovements, int guid) : keyMovements(keyMovements),
		guid(guid)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = keyMovements.size();
		data<<size;

		for(uint16 a = 0; a < size; ++a)
			data<<keyMovements[a];
		data<<guid;
	}

	void Deserialize(ByteBuffer& data)
	{
		keyMovements.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 mov;
			data>>mov;
			keyMovements.push_back(mov);
		}
		data>>guid;
	}
};

#endif