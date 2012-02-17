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

#ifndef __CHARACTER_SPELL_MODIFICATION__
#define __CHARACTER_SPELL_MODIFICATION__

class CharacterSpellModification : public DofusModel
{
public:
	int8 modificationType;
	int16 spellId;
	CharacterBaseCharacteristicPtr value;

	uint16 GetProtocol() const
	{ return CHARACTER_SPELL_MODIFICATION; }

	CharacterSpellModification()
	{
	}

	CharacterSpellModification(int8 modificationType, int16 spellId, CharacterBaseCharacteristic* value) : modificationType(modificationType), spellId(spellId), value(value)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<modificationType<<spellId;
		value->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>modificationType>>spellId;
		value.reset(new CharacterBaseCharacteristic);
		value->Deserialize(data);
	}
};

typedef boost::shared_ptr<CharacterSpellModification> CharacterSpellModificationPtr;

#endif