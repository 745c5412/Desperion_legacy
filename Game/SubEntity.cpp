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

#include "StdAfx.h"

// c'est chiant parfois le c++ :(

SubEntity::SubEntity(int8 bindingPointCategory, int8 bindingPointIndex, EntityLook* look) : bindingPointCategory(bindingPointCategory),
	bindingPointIndex(bindingPointIndex), look(look)
{
}

void SubEntity::Serialize(ByteBuffer& data) const
{
	data<<bindingPointCategory<<bindingPointIndex;
	look->Serialize(data);
}

void SubEntity::Deserialize(ByteBuffer& data)
{
	delete look;
	look = new EntityLook;
	data>>bindingPointCategory>>bindingPointIndex;
	look->Deserialize(data);
}

SubEntity::~SubEntity()
{
	delete look;
}