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

#ifndef __GAME_ACTION_FIGHT_SUMMON_MESSAGE__
#define __GAME_ACTION_FIGHT_SUMMON_MESSAGE__

class GameActionFightSummonMessage : public AbstractGameActionMessage
{
public:
	GameFightFighterInformationsPtr summon;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ACTION_FIGHT_SUMMON; }

	GameActionFightSummonMessage()
	{
	}

	GameActionFightSummonMessage(int16 actionId, int sourceId, GameFightFighterInformations* summon) : AbstractGameActionMessage(actionId, sourceId), summon(summon)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Serialize(data);
		data<<summon->GetProtocol();
		summon->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Deserialize(data);
		uint16 protocol;
		data>>protocol;
		summon.reset(Desperion::ProtocolTypeManager::GetGameFightFighterInformations(protocol));
		summon->Deserialize(data);
	}
};

#endif