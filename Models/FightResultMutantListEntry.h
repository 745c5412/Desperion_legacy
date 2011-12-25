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

#ifndef __FIGHT_RESULT_MUTANT_LIST_ENTRY__
#define __FIGHT_RESULT_MUTANT_LIST_ENTRY__

class FightResultMutantListEntry : public FightResultFighterListEntry
{
public:
	uint16 level;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_MUTANT_LIST_ENTRY; }

	FightResultMutantListEntry()
	{
	}

	FightResultMutantListEntry(int16 outcome, FightLoot* rewards, int id, bool alive, uint16 level) : FightResultFighterListEntry(outcome, rewards, id, alive), level(level)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		FightResultFighterListEntry::Serialize(data);
		data<<level;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightResultFighterListEntry::Deserialize(data);
		data>>level;
	}
};

typedef boost::shared_ptr<FightResultMutantListEntry> FightResultMutantListEntryPtr;

#endif