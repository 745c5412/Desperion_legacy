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

#ifndef __OBJECT_EFFECT_LADDER__
#define __OBJECT_EFFECT_LADDER__

class ObjectEffectLadder : public ObjectEffectCreature
{
public:
	int monsterCount;

	uint16 GetProtocol() const
	{ return OBJECT_EFFECT_LADDER; }

	ObjectEffectLadder()
	{
	}

	ObjectEffectLadder(int16 actionId, int16 monsterFamilyId, int monsterCount) : ObjectEffectCreature(actionId, monsterFamilyId), monsterCount(monsterCount)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		ObjectEffectCreature::Serialize(data);
		data<<monsterCount;
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectEffectCreature::Deserialize(data);
		data>>monsterCount;
	}
};

typedef boost::shared_ptr<ObjectEffectLadder> ObjectEffectLadderPtr;

#endif