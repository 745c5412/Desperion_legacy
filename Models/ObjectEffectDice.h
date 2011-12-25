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

#ifndef __OBJECT_EFFECT_DICE__
#define __OBJECT_EFFECT_DICE__

class ObjectEffectDice : public ObjectEffect
{
public:
	int16 diceNum;
	int16 diceSide;
	int16 diceConst;

	uint16 GetProtocol() const
	{ return OBJECT_EFFECT_DICE; }

	ObjectEffectDice()
	{
	}

	ObjectEffectDice(int16 actionId, int16 diceNum, int16 diceSide, int16 diceConst) : ObjectEffect(actionId), diceNum(diceNum), diceSide(diceSide), diceConst(diceConst)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ObjectEffect::Serialize(data);
		data<<diceNum<<diceSide<<diceConst;
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectEffect::Deserialize(data);
		data>>diceNum>>diceSide>>diceConst;
	}
};

typedef boost::shared_ptr<ObjectEffectDice> ObjectEffectDicePtr;

#endif