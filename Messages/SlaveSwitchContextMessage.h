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

#ifndef __SLAVE_SWITCH_CONTEXT_MESSAGE__
#define __SLAVE_SWITCH_CONTEXT_MESSAGE__

class SlaveSwitchContextMessage : public DofusMessage
{
public:
	int summonerId;
	int slaveId;
	std::vector<SpellItemPtr> slaveSpells;
	CharacterCharacteristicsInformationsPtr slaveStats;

	uint16 GetOpcode() const
	{ return SMSG_SLAVE_SWITCH_CONTEXT; }

	SlaveSwitchContextMessage()
	{
	}

	SlaveSwitchContextMessage(int summonerId, int slaveId, std::vector<SpellItemPtr>& slaveSpells, CharacterCharacteristicsInformations* slaveStats) : summonerId(summonerId), slaveId(slaveId), slaveSpells(slaveSpells), slaveStats(slaveStats)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<summonerId<<slaveId;
		uint16 size = slaveSpells.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			slaveSpells[a]->Serialize(data);
		slaveStats->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>summonerId>>slaveId;
		slaveSpells.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			SpellItemPtr model(new SpellItem);
			model->Deserialize(data);
			slaveSpells.push_back(model);
		}
		slaveStats.reset(new CharacterCharacteristicsInformations);
		slaveStats->Deserialize(data);
	}
};

#endif