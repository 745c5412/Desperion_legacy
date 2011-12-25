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

#ifndef __ABSTRACT_GAME_ACTION_FIGHT_TARGETED_ABILITY_MESSAGE__
#define __ABSTRACT_GAME_ACTION_FIGHT_TARGETED_ABILITY_MESSAGE__

class AbstractGameActionFightTargetedAbilityMessage : public AbstractGameActionMessage
{
public:
	int16 destinationCellId;
	int8 critical;
	bool silentCast;

	uint16 GetOpcode() const
	{ return SMSG_ABSTRACT_GAME_ACTION_FIGHT_TARGETED_ABILITY; }

	AbstractGameActionFightTargetedAbilityMessage()
	{
	}

	AbstractGameActionFightTargetedAbilityMessage(int16 actionId, int sourceId, int16 destinationCellId, int8 critical, bool silentCast) : AbstractGameActionMessage(actionId, sourceId), destinationCellId(destinationCellId), critical(critical), silentCast(silentCast)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Serialize(data);
		data<<destinationCellId<<critical<<silentCast;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Deserialize(data);
		data>>destinationCellId>>critical>>silentCast;
	}
};

#endif