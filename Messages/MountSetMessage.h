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

#ifndef __MOUNT_SET_MESSAGE__
#define __MOUNT_SET_MESSAGE__

class MountSetMessage : public DofusMessage
{
public:
	MountClientDataPtr mountData;

	uint16 GetOpcode() const
	{ return SMSG_MOUNT_SET; }

	MountSetMessage()
	{
	}

	MountSetMessage(MountClientData* mountData) : mountData(mountData)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		mountData->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		mountData.reset(new MountClientData);
		mountData->Deserialize(data);
	}
};

#endif