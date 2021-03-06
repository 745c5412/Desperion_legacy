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

#ifndef __HELLO_CONNECT_MESSAGE__
#define __HELLO_CONNECT_MESSAGE__

class HelloConnectMessage : public DofusMessage
{
public:
	std::string salt;
	std::vector<int8> key;

	uint16 GetOpcode() const
	{ return SMSG_HELLO_CONNECT; }

	HelloConnectMessage()
	{
	}

	HelloConnectMessage(std::string salt, std::vector<int8>& key) : salt(salt), key(key)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<salt;
		uint16 size = key.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<key[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>salt;
		key.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 val;
			data>>val;
			key.push_back(val);
		}
	}
};

#endif