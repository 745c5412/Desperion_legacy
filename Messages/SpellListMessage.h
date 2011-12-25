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

#ifndef __SPELL_LIST_MESSAGE__
#define __SPELL_LIST_MESSAGE__

class SpellListMessage : public DofusMessage
{
public:
	bool spellPrevisualization;
	std::vector<SpellItemPtr> spells;

	uint16 GetOpcode() const
	{ return SMSG_SPELL_LIST; }

	SpellListMessage()
	{
	}

	SpellListMessage(bool spellPrevisualization, std::vector<SpellItemPtr>& spells) : spellPrevisualization(spellPrevisualization), spells(spells)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<spellPrevisualization;
		uint16 size = spells.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			spells[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>spellPrevisualization;
		spells.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			SpellItemPtr model(new SpellItem);
			model->Deserialize(data);
			spells.push_back(model);
		}
	}
};

#endif