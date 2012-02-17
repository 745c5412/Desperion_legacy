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

#ifndef __MOUNT_RENAME_REQUEST_MESSAGE__
#define __MOUNT_RENAME_REQUEST_MESSAGE__

class MountRenameRequestMessage : public DofusMessage
{
public:
	std::string name;
	int64 mountId;

	uint16 GetOpcode() const
	{ return CMSG_MOUNT_RENAME_REQUEST; }

	MountRenameRequestMessage()
	{
	}

	MountRenameRequestMessage(std::string name, int64 mountId) : name(name), mountId(mountId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<name<<mountId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>name>>mountId;
	}
};

#endif