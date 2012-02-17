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

#ifndef __GAME_FIGHT_TURN_LIST_MESSAGE__
#define __GAME_FIGHT_TURN_LIST_MESSAGE__

class GameFightTurnListMessage : public DofusMessage
{
public:
	std::vector<int> ids;
	std::vector<int> deadsIds;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_TURN_LIST; }

	GameFightTurnListMessage()
	{
	}

	GameFightTurnListMessage(std::vector<int>& ids, std::vector<int>& deadsIds) : ids(ids), deadsIds(deadsIds)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = ids.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<ids[a];
		uint16 size = deadsIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<deadsIds[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		ids.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			ids.push_back(val);
		}
		deadsIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			deadsIds.push_back(val);
		}
	}
};

#endif