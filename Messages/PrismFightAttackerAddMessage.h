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

#ifndef __PRISM_FIGHT_ATTACKER_ADD_MESSAGE__
#define __PRISM_FIGHT_ATTACKER_ADD_MESSAGE__

class PrismFightAttackerAddMessage : public DofusMessage
{
public:
	int64 fightId;
	std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr> charactersDescription;

	uint16 GetOpcode() const
	{ return SMSG_PRISM_FIGHT_ATTACKER_ADD; }

	PrismFightAttackerAddMessage()
	{
	}

	PrismFightAttackerAddMessage(int64 fightId, std::vector<CharacterMinimalPlusLookAndGradeInformationsPtr>& charactersDescription) : fightId(fightId), charactersDescription(charactersDescription)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<fightId;
		uint16 size = charactersDescription.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			charactersDescription[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightId;
		charactersDescription.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookAndGradeInformationsPtr model(new CharacterMinimalPlusLookAndGradeInformations);
			model->Deserialize(data);
			charactersDescription.push_back(model);
		}
	}
};

#endif