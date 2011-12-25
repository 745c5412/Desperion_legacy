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

#ifndef __GAME_ACTION_FIGHT_SPELL_CAST_MESSAGE__
#define __GAME_ACTION_FIGHT_SPELL_CAST_MESSAGE__

class GameActionFightSpellCastMessage : public AbstractGameActionFightTargetedAbilityMessage
{
public:
	int16 spellId;
	int8 spellLevel;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ACTION_FIGHT_SPELL_CAST; }

	GameActionFightSpellCastMessage()
	{
	}

	GameActionFightSpellCastMessage(int16 actionId, int sourceId, int16 destinationCellId, int8 critical, bool silentCast, int16 spellId, int8 spellLevel) : AbstractGameActionFightTargetedAbilityMessage(actionId, sourceId, destinationCellId, critical, silentCast), spellId(spellId), spellLevel(spellLevel)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractGameActionFightTargetedAbilityMessage::Serialize(data);
		data<<spellId<<spellLevel;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionFightTargetedAbilityMessage::Deserialize(data);
		data>>spellId>>spellLevel;
	}
};

#endif