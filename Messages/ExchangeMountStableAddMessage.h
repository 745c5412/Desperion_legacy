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

#ifndef __EXCHANGE_MOUNT_STABLE_ADD_MESSAGE__
#define __EXCHANGE_MOUNT_STABLE_ADD_MESSAGE__

class ExchangeMountStableAddMessage : public DofusMessage
{
public:
	MountClientDataPtr mountDescription;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_MOUNT_STABLE_ADD; }

	ExchangeMountStableAddMessage()
	{
	}

	ExchangeMountStableAddMessage(MountClientData* mountDescription) : mountDescription(mountDescription)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		mountDescription->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		mountDescription.reset(new MountClientData);
		mountDescription->Deserialize(data);
	}
};

#endif