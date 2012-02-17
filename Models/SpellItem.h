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

#ifndef __SPELL_ITEM__
#define __SPELL_ITEM__

class SpellItem : public Item
{
public:
	uint8 position;
	int spellId;
	int8 spellLevel;

	uint16 GetProtocol() const
	{ return SPELL_ITEM; }

	SpellItem()
	{
	}

	SpellItem(int16 oldCellId, int16 newCellId, uint8 position, int spellId, int8 spellLevel) : Item(oldCellId, newCellId), position(position), spellId(spellId), spellLevel(spellLevel)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		Item::Serialize(data);
		data<<position<<spellId<<spellLevel;
	}

	void Deserialize(ByteBuffer& data)
	{
		Item::Deserialize(data);
		data>>position>>spellId>>spellLevel;
	}
};

typedef boost::shared_ptr<SpellItem> SpellItemPtr;

#endif