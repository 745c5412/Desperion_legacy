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

#ifndef __SYSTEM_MESSAGE_DISPLAY_MESSAGE__
#define __SYSTEM_MESSAGE_DISPLAY_MESSAGE__

class SystemMessageDisplayMessage : public DofusMessage
{
public:
	bool hangUp;
	int16 msgId;
	std::vector<std::string> parameters;

	uint16 GetOpcode() const
	{ return SMSG_SYSTEM_MESSAGE_DISPLAY; }

	SystemMessageDisplayMessage()
	{
	}

	SystemMessageDisplayMessage(bool hangUp, int16 msgId, std::vector<std::string>& parameters) : hangUp(hangUp), msgId(msgId), parameters(parameters)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<hangUp<<msgId;
		uint16 size = parameters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<parameters[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>hangUp>>msgId;
		parameters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string val;
			data>>val;
			parameters.push_back(val);
		}
	}
};

#endif