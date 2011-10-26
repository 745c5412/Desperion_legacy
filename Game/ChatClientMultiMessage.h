/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __CHAT_CLIENT_MULTI_MESSAGE__
#define __CHAT_CLIENT_MULTI_MESSAGE__

enum ChatChannelsMulti
{
	MULTI_CHANNEL_GLOBAL = 0,
	MULTI_CHANNEL_TEAM = 1,
	MULTI_CHANNEL_GUILD = 2,
	MULTI_CHANNEL_ALIGN = 3,
	MULTI_CHANNEL_PARTY = 4,
	MULTI_CHANNEL_SALES = 5,
	MULTI_CHANNEL_SEEK = 6,
	MULTI_CHANNEL_NOOB = 7,
	MULTI_CHANNEL_ADMIN = 8,
	MULTI_CHANNEL_ADS = 12,
	MULTI_CHANNEL_ARENA = 13,
};

class ChatClientMultiMessage : public ChatAbstractClientMessage
{
public:
	int8 channel;

	virtual uint32 GetOpcode() const
	{ return CMSG_CHAT_CLIENT_MULTI; }

	ChatClientMultiMessage(ByteBuffer& data) : ChatAbstractClientMessage(data)
	{
		data>>channel;
	}
};

#endif