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

#ifndef __SERVERS_LIST_MESSAGE__
#define __SERVERS_LIST_MESSAGE__

class ServersListMessage : public DofusMessage
{
public:
	std::vector<GameServerInformationsPtr> servers;

	uint16 GetOpcode() const
	{ return SMSG_SERVERS_LIST; }

	ServersListMessage()
	{
	}

	ServersListMessage(std::vector<GameServerInformationsPtr>& servers) : servers(servers)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = servers.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			servers[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		servers.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameServerInformationsPtr model(new GameServerInformations);
			model->Deserialize(data);
			servers.push_back(model);
		}
	}
};

#endif