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

#ifndef __ORIENTED_OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY__
#define __ORIENTED_OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY__

class OrientedObjectItemWithLookInRolePlay : public ObjectItemWithLookInRolePlay
{
public:
	int8 direction;

	uint16 GetProtocol() const
	{ return ORIENTED_OBJECT_ITEM_WITH_LOOK_IN_ROLE_PLAY; }

	OrientedObjectItemWithLookInRolePlay()
	{
	}

	OrientedObjectItemWithLookInRolePlay(int16 cellId, int16 objectGID, EntityLook* entityLook, int8 direction) : ObjectItemWithLookInRolePlay(cellId, objectGID, entityLook), direction(direction)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ObjectItemWithLookInRolePlay::Serialize(data);
		data<<direction;
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectItemWithLookInRolePlay::Deserialize(data);
		data>>direction;
	}
};

typedef boost::shared_ptr<OrientedObjectItemWithLookInRolePlay> OrientedObjectItemWithLookInRolePlayPtr;

#endif