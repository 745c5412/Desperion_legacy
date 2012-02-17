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

#ifndef __NOTIFICATION_BY_SERVER_MESSAGE__
#define __NOTIFICATION_BY_SERVER_MESSAGE__

class NotificationByServerMessage : public DofusMessage
{
public:
	uint16 id;
	std::vector<std::string> parameters;
	bool forceOpen;

	uint16 GetOpcode() const
	{ return SMSG_NOTIFICATION_BY_SERVER; }

	NotificationByServerMessage()
	{
	}

	NotificationByServerMessage(uint16 id, std::vector<std::string>& parameters, bool forceOpen) : id(id), parameters(parameters), forceOpen(forceOpen)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<id;
		uint16 size = parameters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<parameters[a];
		data<<forceOpen;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>id;
		parameters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string val;
			data>>val;
			parameters.push_back(val);
		}
		data>>forceOpen;
	}
};

#endif