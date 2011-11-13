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

#ifndef __OBJECT_EFFECT_MOUNT__
#define __OBJECT_EFFECT_MOUNT__

struct PlayerItemEffectMount;

class ObjectEffectMount : public ObjectEffect
{
public:
	int mountId;
	uint64 date;
	int16 modelId;
	
	virtual uint16 GetProtocol() const
	{ return OBJECT_EFFECT_MOUNT; }
	
	ObjectEffectMount()
	{
	}
	
	ObjectEffectMount(PlayerItemEffectMount*);
	
	virtual void Serialize(ByteBuffer& data)
	{
		ObjectEffect::Serialize(data);
		data<<mountId<<date<<modelId;
	}
	
	virtual void Deserialize(ByteBuffer& data)
	{
		ObjectEffect::Deserialize(data);
		data>>mountId>>date>>modelId;
	}
};

#endif