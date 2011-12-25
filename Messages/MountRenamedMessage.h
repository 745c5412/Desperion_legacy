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

#ifndef __MOUNT_RENAMED_MESSAGE__
#define __MOUNT_RENAMED_MESSAGE__

class MountRenamedMessage : public DofusMessage
{
public:
	int64 mountId;
	std::string name;

	uint16 GetOpcode() const
	{ return SMSG_MOUNT_RENAMED; }

	MountRenamedMessage()
	{
	}

	MountRenamedMessage(int64 mountId, std::string name) : mountId(mountId), name(name)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<mountId<<name;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>mountId>>name;
	}
};

#endif