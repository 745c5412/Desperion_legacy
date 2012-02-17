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

#ifndef __NOTIFICATION_LIST_MESSAGE__
#define __NOTIFICATION_LIST_MESSAGE__

class NotificationListMessage : public DofusMessage
{
public:
	std::vector<int> flags;

	uint16 GetOpcode() const
	{ return SMSG_NOTIFICATION_LIST; }

	NotificationListMessage()
	{
	}

	NotificationListMessage(std::vector<int>& flags) : flags(flags)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = flags.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<flags[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		flags.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			flags.push_back(val);
		}
	}
};

#endif