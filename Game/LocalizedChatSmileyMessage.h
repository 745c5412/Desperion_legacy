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

#ifndef __LOCALIZED_CHAT_SMILEY_MESSAGE__
#define __LOCALIZED_CHAT_SMILEY_MESSAGE__

class LocalizedChatSmileyMessage : public ChatSmileyMessage
{
public:
	int16 cellId;

	virtual uint16 GetOpcode() const
	{ return SMSG_LOCALIZED_CHAT_SMILEY; }

	LocalizedChatSmileyMessage()
	{
	}

	LocalizedChatSmileyMessage(int entityId, int8 smileyId, int accountId, int16 cellId)
		: ChatSmileyMessage(entityId, smileyId, accountId), cellId(cellId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ChatSmileyMessage::Serialize(data);
		data<<cellId;
	}

	void Deserialize(ByteBuffer& data)
	{
		ChatSmileyMessage::Deserialize(data);
		data>>cellId;
	}
};

#endif