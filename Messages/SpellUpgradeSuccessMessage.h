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

#ifndef __SPELL_UPGRADE_SUCCESS_MESSAGE__
#define __SPELL_UPGRADE_SUCCESS_MESSAGE__

class SpellUpgradeSuccessMessage : public DofusMessage
{
public:
	int spellId;
	int8 spellLevel;

	uint16 GetOpcode() const
	{ return SMSG_SPELL_UPGRADE_SUCCESS; }

	SpellUpgradeSuccessMessage()
	{
	}

	SpellUpgradeSuccessMessage(int spellId, int8 spellLevel) : spellId(spellId), spellLevel(spellLevel)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<spellId<<spellLevel;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>spellId>>spellLevel;
	}
};

#endif