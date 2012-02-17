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

#ifndef __GAME_ACTION_FIGHT_TACKLED_MESSAGE__
#define __GAME_ACTION_FIGHT_TACKLED_MESSAGE__

class GameActionFightTackledMessage : public AbstractGameActionMessage
{
public:
	std::vector<int> tacklersIds;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ACTION_FIGHT_TACKLED; }

	GameActionFightTackledMessage()
	{
	}

	GameActionFightTackledMessage(int16 actionId, int sourceId, std::vector<int>& tacklersIds) : AbstractGameActionMessage(actionId, sourceId), tacklersIds(tacklersIds)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractGameActionMessage::Serialize(data);
		uint16 size = tacklersIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<tacklersIds[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Deserialize(data);
		tacklersIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			tacklersIds.push_back(val);
		}
	}
};

#endif