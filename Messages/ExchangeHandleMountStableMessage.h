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

#ifndef __EXCHANGE_HANDLE_MOUNT_STABLE_MESSAGE__
#define __EXCHANGE_HANDLE_MOUNT_STABLE_MESSAGE__

class ExchangeHandleMountStableMessage : public DofusMessage
{
public:
	int8 actionType;
	int rideId;

	uint16 GetOpcode() const
	{ return CMSG_EXCHANGE_HANDLE_MOUNT_STABLE; }

	ExchangeHandleMountStableMessage()
	{
	}

	ExchangeHandleMountStableMessage(int8 actionType, int rideId) : actionType(actionType), rideId(rideId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<actionType<<rideId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>actionType>>rideId;
	}
};

#endif