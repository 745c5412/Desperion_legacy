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

#ifndef __CHAT_ABSTRACT_SERVER_MESSAGE__
#define __CHAT_ABSTRACT_SERVER_MESSAGE__

enum ChatActivableChannels
{
	CHANNEL_GLOBAL = 0,
	CHANNEL_TEAM = 1,
	CHANNEL_GUILD = 2,
	CHANNEL_ALIGN = 3,
	CHANNEL_PARTY = 4,
	CHANNEL_SALES = 5,
	CHANNEL_SEEK = 6,
	CHANNEL_NOOB = 7,
	CHANNEL_ADMIN = 8,
	CHANNEL_ADS = 12,
	CHANNEL_ARENA = 13,
	PSEUDO_CHANNEL_PRIVATE = 9,
	PSEUDO_CHANNEL_INFO = 10,
	PSEUDO_CHANNEL_FIGHT_LOG = 11,
};

class ChatAbstractServerMessage : public DofusMessage
{
public:
	int8 channel;
	std::string content, fingerprint;
	int timestamp;

	virtual uint16 GetOpcode() const
	{ return SMSG_CHAT_ABSTRACT_SERVER; }

	ChatAbstractServerMessage()
	{
	}

	ChatAbstractServerMessage(int8 channel, std::string content, int timestamp, std::string fingerprint) : channel(channel),
		content(content), timestamp(timestamp), fingerprint(fingerprint)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<channel<<content<<timestamp<<fingerprint;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>channel>>content>>timestamp>>fingerprint;
	}
};

#endif