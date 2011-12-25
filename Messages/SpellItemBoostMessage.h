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

#ifndef __SPELL_ITEM_BOOST_MESSAGE__
#define __SPELL_ITEM_BOOST_MESSAGE__

class SpellItemBoostMessage : public DofusMessage
{
public:
	int statId;
	int16 spellId;
	int16 value;

	uint16 GetOpcode() const
	{ return SMSG_SPELL_ITEM_BOOST; }

	SpellItemBoostMessage()
	{
	}

	SpellItemBoostMessage(int statId, int16 spellId, int16 value) : statId(statId), spellId(spellId), value(value)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<statId<<spellId<<value;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>statId>>spellId>>value;
	}
};

#endif