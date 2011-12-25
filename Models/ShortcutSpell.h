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

#ifndef __SHORTCUT_SPELL__
#define __SHORTCUT_SPELL__

class ShortcutSpell : public Shortcut
{
public:
	int16 spellId;

	uint16 GetProtocol() const
	{ return SHORTCUT_SPELL; }

	ShortcutSpell()
	{
	}

	ShortcutSpell(int8 error, int16 spellId) : Shortcut(error), spellId(spellId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		Shortcut::Serialize(data);
		data<<spellId;
	}

	void Deserialize(ByteBuffer& data)
	{
		Shortcut::Deserialize(data);
		data>>spellId;
	}
};

typedef boost::shared_ptr<ShortcutSpell> ShortcutSpellPtr;

#endif