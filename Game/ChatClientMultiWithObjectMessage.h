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

#ifndef __CHAT_CLIENT_MULTI_WITH_OBJECT_MESSAGE__
#define __CHAT_CLIENT_MULTI_WITH_OBJECT_MESSAGE__

class ChatClientMultiWithObjectMessage : public ChatClientMultiMessage
{
public:
	std::vector<ObjectItem> objects;

	virtual uint32 GetOpcode() const
	{ return CMSG_CHAT_CLIENT_MULTI_WITH_OBJECT; }

	ChatClientMultiWithObjectMessage(ByteBuffer& data) : ChatClientMultiMessage(data)
	{
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItem obj;
			obj.Init(data);
			objects.push_back(obj);
		}
	}
};

#endif