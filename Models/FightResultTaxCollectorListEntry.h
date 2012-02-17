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

#ifndef __FIGHT_RESULT_TAX_COLLECTOR_LIST_ENTRY__
#define __FIGHT_RESULT_TAX_COLLECTOR_LIST_ENTRY__

class FightResultTaxCollectorListEntry : public FightResultFighterListEntry
{
public:
	uint8 level;
	BasicGuildInformationsPtr guildInfo;
	int experienceForGuild;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_TAX_COLLECTOR_LIST_ENTRY; }

	FightResultTaxCollectorListEntry()
	{
	}

	FightResultTaxCollectorListEntry(int16 outcome, FightLoot* rewards, int id, bool alive, uint8 level, BasicGuildInformations* guildInfo, int experienceForGuild) : FightResultFighterListEntry(outcome, rewards, id, alive), level(level), guildInfo(guildInfo), experienceForGuild(experienceForGuild)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FightResultFighterListEntry::Serialize(data);
		data<<level;
		guildInfo->Serialize(data);
		data<<experienceForGuild;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightResultFighterListEntry::Deserialize(data);
		data>>level;
		guildInfo.reset(new BasicGuildInformations);
		guildInfo->Deserialize(data);
		data>>experienceForGuild;
	}
};

typedef boost::shared_ptr<FightResultTaxCollectorListEntry> FightResultTaxCollectorListEntryPtr;

#endif