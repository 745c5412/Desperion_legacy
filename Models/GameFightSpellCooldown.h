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

#ifndef __GAME_FIGHT_SPELL_COOLDOWN__
#define __GAME_FIGHT_SPELL_COOLDOWN__

class GameFightSpellCooldown : public DofusModel
{
public:
	int spellId;
	int8 cooldown;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_SPELL_COOLDOWN; }

	GameFightSpellCooldown()
	{
	}

	GameFightSpellCooldown(int spellId, int8 cooldown) : spellId(spellId), cooldown(cooldown)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<spellId<<cooldown;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>spellId>>cooldown;
	}
};

typedef boost::shared_ptr<GameFightSpellCooldown> GameFightSpellCooldownPtr;

#endif