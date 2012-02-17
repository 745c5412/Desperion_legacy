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

#ifndef __FIGHT_TEMPORARY_BOOST_STATE_EFFECT__
#define __FIGHT_TEMPORARY_BOOST_STATE_EFFECT__

class FightTemporaryBoostStateEffect : public FightTemporaryBoostEffect
{
public:
	int16 stateId;

	uint16 GetProtocol() const
	{ return FIGHT_TEMPORARY_BOOST_STATE_EFFECT; }

	FightTemporaryBoostStateEffect()
	{
	}

	FightTemporaryBoostStateEffect(int uid, int targetId, int16 turnDuration, int8 dispelable, int16 spellId, int parentBoostUid, int16 delta, int16 stateId) : FightTemporaryBoostEffect(uid, targetId, turnDuration, dispelable, spellId, parentBoostUid, delta), stateId(stateId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FightTemporaryBoostEffect::Serialize(data);
		data<<stateId;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightTemporaryBoostEffect::Deserialize(data);
		data>>stateId;
	}
};

typedef boost::shared_ptr<FightTemporaryBoostStateEffect> FightTemporaryBoostStateEffectPtr;

#endif