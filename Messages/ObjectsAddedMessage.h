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

#ifndef __OBJECTS_ADDED_MESSAGE__
#define __OBJECTS_ADDED_MESSAGE__

class ObjectsAddedMessage : public DofusMessage
{
public:
	std::vector<ObjectItemPtr> object;

	uint16 GetOpcode() const
	{ return SMSG_OBJECTS_ADDED; }

	ObjectsAddedMessage()
	{
	}

	ObjectsAddedMessage(std::vector<ObjectItemPtr>& object) : object(object)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = object.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			object[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		object.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemPtr model(new ObjectItem);
			model->Deserialize(data);
			object.push_back(model);
		}
	}
};

#endif