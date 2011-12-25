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

#ifndef __PRISM_FIGHT_DEFENDERS_STATE_MESSAGE__
#define __PRISM_FIGHT_DEFENDERS_STATE_MESSAGE__

class PrismFightDefendersStateMessage : public DofusMessage
{
public:
	int64 fightId;
	std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr> mainFighters;
	std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr> reserveFighters;

	uint16 GetOpcode() const
	{ return SMSG_PRISM_FIGHT_DEFENDERS_STATE; }

	PrismFightDefendersStateMessage()
	{
	}

	PrismFightDefendersStateMessage(int64 fightId, std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr>& mainFighters, std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr>& reserveFighters) : fightId(fightId), mainFighters(mainFighters), reserveFighters(reserveFighters)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<fightId;
		uint16 size = mainFighters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			mainFighters[a]->Serialize(data);
		uint16 size = reserveFighters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			reserveFighters[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightId;
		mainFighters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookAndGradeInformationsPtr model(new CharacterMinimalPlusLookAndGradeInformations);
			model->Deserialize(data);
			mainFighters.push_back(model);
		}
		reserveFighters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookAndGradeInformationsPtr model(new CharacterMinimalPlusLookAndGradeInformations);
			model->Deserialize(data);
			reserveFighters.push_back(model);
		}
	}
};

#endif