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

#ifndef __FIGHT_RESULT_LIST_ENTRY__
#define __FIGHT_RESULT_LIST_ENTRY__

class FightResultListEntry : public DofusModel
{
public:
	int16 outcome;
	FightLootPtr rewards;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_LIST_ENTRY; }

	FightResultListEntry()
	{
	}

	FightResultListEntry(int16 outcome, FightLoot* rewards) : outcome(outcome), rewards(rewards)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<outcome;
		rewards->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>outcome;
		rewards.reset(new FightLoot);
		rewards->Deserialize(data);
	}
};

typedef boost::shared_ptr<FightResultListEntry> FightResultListEntryPtr;

#endif