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

#ifndef __LIVING_OBJECT_MESSAGE_MESSAGE__
#define __LIVING_OBJECT_MESSAGE_MESSAGE__

class LivingObjectMessageMessage : public DofusMessage
{
public:
	int16 msgId;
	uint32 timeStamp;
	std::string owner;
	uint32 objectGenericId;

	uint16 GetOpcode() const
	{ return SMSG_LIVING_OBJECT_MESSAGE; }

	LivingObjectMessageMessage()
	{
	}

	LivingObjectMessageMessage(int16 msgId, uint32 timeStamp, std::string owner, uint32 objectGenericId) : msgId(msgId), timeStamp(timeStamp), owner(owner), objectGenericId(objectGenericId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<msgId<<timeStamp<<owner<<objectGenericId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>msgId>>timeStamp>>owner>>objectGenericId;
	}
};

#endif