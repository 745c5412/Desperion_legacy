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

#ifndef __GAME_FIGHT_STARTING_MESSAGE__
#define __GAME_FIGHT_STARTING_MESSAGE__

class GameFightStartingMessage : public DofusMessage
{
public:
	int8 fightType;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_STARTING; }

	GameFightStartingMessage()
	{
	}

	GameFightStartingMessage(int8 fightType) : fightType(fightType)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<fightType;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightType;
	}
};

#endif