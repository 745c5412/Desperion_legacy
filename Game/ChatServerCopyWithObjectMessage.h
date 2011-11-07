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

#ifndef __CHAT_SERVER_COPY_WITH_OBJECT_MESSAGE__
#define __CHAT_SERVER_COPY_WITH_OBJECT_MESSAGE__

class ChatServerCopyWithObjectMessage : public ChatServerCopyMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CHAT_SERVER_COPY_WITH_OBJECT; }

	ChatServerCopyWithObjectMessage(int8 channel, std::string content, int timestamp, std::string fingerprint, int receivedId, 
		std::string receivedName, std::vector<ObjectItem>& objects) : ChatServerCopyMessage(channel, content, timestamp, fingerprint, 
		receivedId, receivedName)
	{
		uint16 size = objects.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			objects[a].FromThis();
			m_buffer<<objects[a];
		}
	}
};

#endif