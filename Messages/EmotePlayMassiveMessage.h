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

#ifndef __EMOTE_PLAY_MASSIVE_MESSAGE__
#define __EMOTE_PLAY_MASSIVE_MESSAGE__

class EmotePlayMassiveMessage : public EmotePlayAbstractMessage
{
public:
	std::vector<int> actorIds;

	uint16 GetOpcode() const
	{ return SMSG_EMOTE_PLAY_MASSIVE; }

	EmotePlayMassiveMessage()
	{
	}

	EmotePlayMassiveMessage(int8 emoteId, int64 emoteStartTime, std::vector<int>& actorIds) : EmotePlayAbstractMessage(emoteId, emoteStartTime), actorIds(actorIds)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		EmotePlayAbstractMessage::Serialize(data);
		uint16 size = actorIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<actorIds[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		EmotePlayAbstractMessage::Deserialize(data);
		actorIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			actorIds.push_back(val);
		}
	}
};

#endif