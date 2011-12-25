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

#ifndef __ABSTRACT_FIGHT_DISPELLABLE_EFFECT__
#define __ABSTRACT_FIGHT_DISPELLABLE_EFFECT__

class AbstractFightDispellableEffect : public DofusModel
{
public:
	int uid;
	int targetId;
	int16 turnDuration;
	int8 dispelable;
	int16 spellId;
	int parentBoostUid;

	uint16 GetProtocol() const
	{ return ABSTRACT_FIGHT_DISPELLABLE_EFFECT; }

	AbstractFightDispellableEffect()
	{
	}

	AbstractFightDispellableEffect(int uid, int targetId, int16 turnDuration, int8 dispelable, int16 spellId, int parentBoostUid) : uid(uid), targetId(targetId), turnDuration(turnDuration), dispelable(dispelable), spellId(spellId), parentBoostUid(parentBoostUid)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<uid<<targetId<<turnDuration<<dispelable<<spellId<<parentBoostUid;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>uid>>targetId>>turnDuration>>dispelable>>spellId>>parentBoostUid;
	}
};

typedef boost::shared_ptr<AbstractFightDispellableEffect> AbstractFightDispellableEffectPtr;

#endif