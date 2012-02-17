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

#ifndef __FIGHT_TRIGGERED_EFFECT__
#define __FIGHT_TRIGGERED_EFFECT__

class FightTriggeredEffect : public AbstractFightDispellableEffect
{
public:
	int param1;
	int param2;
	int param3;
	int16 delay;

	uint16 GetProtocol() const
	{ return FIGHT_TRIGGERED_EFFECT; }

	FightTriggeredEffect()
	{
	}

	FightTriggeredEffect(int uid, int targetId, int16 turnDuration, int8 dispelable, int16 spellId, int parentBoostUid, int param1, int param2, int param3, int16 delay) : AbstractFightDispellableEffect(uid, targetId, turnDuration, dispelable, spellId, parentBoostUid), param1(param1), param2(param2), param3(param3), delay(delay)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractFightDispellableEffect::Serialize(data);
		data<<param1<<param2<<param3<<delay;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractFightDispellableEffect::Deserialize(data);
		data>>param1>>param2>>param3>>delay;
	}
};

typedef boost::shared_ptr<FightTriggeredEffect> FightTriggeredEffectPtr;

#endif