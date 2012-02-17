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

#ifndef __GAME_ACTION_FIGHT_TRIGGER_GLYPH_TRAP_MESSAGE__
#define __GAME_ACTION_FIGHT_TRIGGER_GLYPH_TRAP_MESSAGE__

class GameActionFightTriggerGlyphTrapMessage : public AbstractGameActionMessage
{
public:
	int16 markId;
	int triggeringCharacterId;
	int16 triggeredSpellId;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ACTION_FIGHT_TRIGGER_GLYPH_TRAP; }

	GameActionFightTriggerGlyphTrapMessage()
	{
	}

	GameActionFightTriggerGlyphTrapMessage(int16 actionId, int sourceId, int16 markId, int triggeringCharacterId, int16 triggeredSpellId) : AbstractGameActionMessage(actionId, sourceId), markId(markId), triggeringCharacterId(triggeringCharacterId), triggeredSpellId(triggeredSpellId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractGameActionMessage::Serialize(data);
		data<<markId<<triggeringCharacterId<<triggeredSpellId;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Deserialize(data);
		data>>markId>>triggeringCharacterId>>triggeredSpellId;
	}
};

#endif