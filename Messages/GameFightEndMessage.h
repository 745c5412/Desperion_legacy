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

#ifndef __GAME_FIGHT_END_MESSAGE__
#define __GAME_FIGHT_END_MESSAGE__

class GameFightEndMessage : public DofusMessage
{
public:
	int duration;
	int16 ageBonus;
	std::vector<FightResultListEntryPtr> results;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_END; }

	GameFightEndMessage()
	{
	}

	GameFightEndMessage(int duration, int16 ageBonus, std::vector<FightResultListEntryPtr>& results) : duration(duration), ageBonus(ageBonus), results(results)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<duration<<ageBonus;
		uint16 size = results.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<results[a]->GetProtocol();
			results[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>duration>>ageBonus;
		results.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FightResultListEntryPtr model(Desperion::ProtocolTypeManager::GetFightResultListEntry(protocol));
			model->Deserialize(data);
			results.push_back(model);
		}
	}
};

#endif