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

#ifndef __PRISM_FIGHT_DEFENDERS_SWAP_MESSAGE__
#define __PRISM_FIGHT_DEFENDERS_SWAP_MESSAGE__

class PrismFightDefendersSwapMessage : public DofusMessage
{
public:
	int64 fightId;
	int fighterId1;
	int fighterId2;

	uint16 GetOpcode() const
	{ return SMSG_PRISM_FIGHT_DEFENDERS_SWAP; }

	PrismFightDefendersSwapMessage()
	{
	}

	PrismFightDefendersSwapMessage(int64 fightId, int fighterId1, int fighterId2) : fightId(fightId), fighterId1(fighterId1), fighterId2(fighterId2)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<fightId<<fighterId1<<fighterId2;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightId>>fighterId1>>fighterId2;
	}
};

#endif