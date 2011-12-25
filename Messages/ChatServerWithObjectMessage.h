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

#ifndef __CHAT_SERVER_WITH_OBJECT_MESSAGE__
#define __CHAT_SERVER_WITH_OBJECT_MESSAGE__

class ChatServerWithObjectMessage : public ChatServerMessage
{
public:
	std::vector<ObjectItemPtr> objects;

	uint16 GetOpcode() const
	{ return SMSG_CHAT_SERVER_WITH_OBJECT; }

	ChatServerWithObjectMessage()
	{
	}

	ChatServerWithObjectMessage(int8 channel, std::string content, int timestamp, std::string fingerprint, int senderId, std::string senderName, int senderAccountId, std::vector<ObjectItemPtr>& objects) : ChatServerMessage(channel, content, timestamp, fingerprint, senderId, senderName, senderAccountId), objects(objects)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ChatServerMessage::Serialize(data);
		uint16 size = objects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objects[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		ChatServerMessage::Deserialize(data);
		objects.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemPtr model(new ObjectItem);
			model->Deserialize(data);
			objects.push_back(model);
		}
	}
};

#endif