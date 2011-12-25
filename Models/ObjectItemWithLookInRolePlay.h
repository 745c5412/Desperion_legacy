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

#ifndef __OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY__
#define __OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY__

class ObjectItemWithLookInRolePlay : public ObjectItemInRolePlay
{
public:
	EntityLookPtr entityLook;

	uint16 GetProtocol() const
	{ return OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY; }

	ObjectItemWithLookInRolePlay()
	{
	}

	ObjectItemWithLookInRolePlay(int16 cellId, int16 objectGID, EntityLook* entityLook) : ObjectItemInRolePlay(cellId, objectGID), entityLook(entityLook)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ObjectItemInRolePlay::Serialize(data);
		entityLook->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectItemInRolePlay::Deserialize(data);
		entityLook.reset(new EntityLook);
		entityLook->Deserialize(data);
	}
};

typedef boost::shared_ptr<ObjectItemWithLookInRolePlay> ObjectItemWithLookInRolePlayPtr;

#endif