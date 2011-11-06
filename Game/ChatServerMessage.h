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

#ifndef __CHAT_SERVER_MESSAGE__
#define __CHAT_SERVER_MESSAGE__

class ChatServerMessage : public ChatAbstractServerMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CHAT_SERVER; }

	ChatServerMessage(int8 channel, std::string content, int timestamp, std::string fingerprint, int senderId, std::string senderName,
		int senderAccountId) : ChatAbstractServerMessage(channel, content, timestamp, fingerprint)
	{
		m_buffer<<senderId<<senderName<<senderAccountId;
	}
};

#endif