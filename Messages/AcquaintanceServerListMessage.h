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

#ifndef __ACQUAINTANCE_SERVER_LIST_MESSAGE__
#define __ACQUAINTANCE_SERVER_LIST_MESSAGE__

class AcquaintanceServerListMessage : public DofusMessage
{
public:
	std::vector<int16> servers;

	uint16 GetOpcode() const
	{ return SMSG_ACQUAINTANCE_SERVER_LIST; }

	AcquaintanceServerListMessage()
	{
	}

	AcquaintanceServerListMessage(std::vector<int16>& servers) : servers(servers)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = servers.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<servers[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		servers.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 val;
			data>>val;
			servers.push_back(val);
		}
	}
};

#endif