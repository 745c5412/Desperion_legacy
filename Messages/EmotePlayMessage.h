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

#ifndef __EMOTE_PLAY_MESSAGE__
#define __EMOTE_PLAY_MESSAGE__

class EmotePlayMessage : public EmotePlayAbstractMessage
{
public:
	int actorId;
	int accountId;

	uint16 GetOpcode() const
	{ return SMSG_EMOTE_PLAY; }

	EmotePlayMessage()
	{
	}

	EmotePlayMessage(int8 emoteId, int64 emoteStartTime, int actorId, int accountId) : EmotePlayAbstractMessage(emoteId, emoteStartTime), actorId(actorId), accountId(accountId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		EmotePlayAbstractMessage::Serialize(data);
		data<<actorId<<accountId;
	}

	void Deserialize(ByteBuffer& data)
	{
		EmotePlayAbstractMessage::Deserialize(data);
		data>>actorId>>accountId;
	}
};

#endif