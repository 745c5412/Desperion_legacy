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

#ifndef __FIGHT_RESULT_PLAYER_LIST_ENTRY__
#define __FIGHT_RESULT_PLAYER_LIST_ENTRY__

class FightResultPlayerListEntry : public FightResultFighterListEntry
{
public:
	uint8 level;
	std::vector<FightResultAdditionalDataPtr> additional;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_PLAYER_LIST_ENTRY; }

	FightResultPlayerListEntry()
	{
	}

	FightResultPlayerListEntry(int16 outcome, FightLoot* rewards, int id, bool alive, uint8 level, std::vector<FightResultAdditionalDataPtr>& additional) : FightResultFighterListEntry(outcome, rewards, id, alive), level(level), additional(additional)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FightResultFighterListEntry::Serialize(data);
		data<<level;
		uint16 size = additional.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<additional[a]->GetProtocol();
			additional[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		FightResultFighterListEntry::Deserialize(data);
		data>>level;
		additional.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FightResultAdditionalDataPtr model(Desperion::ProtocolTypeManager::GetFightResultAdditionalData(protocol));
			model->Deserialize(data);
			additional.push_back(model);
		}
	}
};

typedef boost::shared_ptr<FightResultPlayerListEntry> FightResultPlayerListEntryPtr;

#endif