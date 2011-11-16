#include "StdAfx.h"

SubEntity::SubEntity(int8 bindingPointCategory, int8 bindingPointIndex, EntityLook* look) : bindingPointCategory(bindingPointCategory),
	bindingPointIndex(bindingPointIndex), look(look)
{
}

void SubEntity::Serialize(ByteBuffer& data)
{
	data<<bindingPointCategory<<bindingPointIndex;
	look->Serialize(data);
}

void SubEntity::Deserialize(ByteBuffer& data)
{
	data>>bindingPointCategory>>bindingPointIndex;
	look->Deserialize(data);
}

SubEntity::~SubEntity()
{
	delete look;
}