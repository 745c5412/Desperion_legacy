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

#ifndef __OBJECTS_DELETED_MESSAGE__
#define __OBJECTS_DELETED_MESSAGE__

class ObjectsDeletedMessage : public DofusMessage
{
public:
	std::vector<int> objectUIDs;

	virtual uint16 GetOpcode() const
	{ return SMSG_OBJECTS_DELETED; }

	ObjectsDeletedMessage()
	{
	}

	ObjectsDeletedMessage(std::vector<int>& objectUIDs) : objectUIDs(objectUIDs)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = objectUIDs.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<objectUIDs[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		objectUIDs.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int obj;
			data>>obj;
			objectUIDs.push_back(obj);
		}
	}
};

#endif