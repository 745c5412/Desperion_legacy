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

#ifndef __OBJECTS_QUANTITY_MESSAGE__
#define __OBJECTS_QUANTITY_MESSAGE__

class ObjectsQuantityMessage : public DofusMessage
{
public:
	std::vector<ObjectItemQuantityPtr> objectsUIDAndQty;

	uint16 GetOpcode() const
	{ return SMSG_OBJECTS_QUANTITY; }

	ObjectsQuantityMessage()
	{
	}

	ObjectsQuantityMessage(std::vector<ObjectItemQuantityPtr>& objectsUIDAndQty) : objectsUIDAndQty(objectsUIDAndQty)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = objectsUIDAndQty.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objectsUIDAndQty[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		objectsUIDAndQty.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemQuantityPtr model(new ObjectItemQuantity);
			model->Deserialize(data);
			objectsUIDAndQty.push_back(model);
		}
	}
};

#endif