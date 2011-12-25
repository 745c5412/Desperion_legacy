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

#ifndef __NOTIFICATION_UPDATE_FLAG_MESSAGE__
#define __NOTIFICATION_UPDATE_FLAG_MESSAGE__

class NotificationUpdateFlagMessage : public DofusMessage
{
public:
	int16 index;

	uint16 GetOpcode() const
	{ return CMSG_NOTIFICATION_UPDATE_FLAG; }

	NotificationUpdateFlagMessage()
	{
	}

	NotificationUpdateFlagMessage(int16 index) : index(index)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<index;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>index;
	}
};

#endif