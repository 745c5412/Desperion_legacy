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

#ifndef __GAME_ROLE_PLAY_NPC_WITH_QUEST_INFORMATIONS__
#define __GAME_ROLE_PLAY_NPC_WITH_QUEST_INFORMATIONS__

class GameRolePlayNpcWithQuestInformations : public GameRolePlayNpcInformations
{
public:
	GameRolePlayNpcQuestFlagPtr questFlag;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_NPC_WITH_QUEST_INFORMATIONS; }

	GameRolePlayNpcWithQuestInformations()
	{
	}

	GameRolePlayNpcWithQuestInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int16 npcId, bool sex, int16 specialArtworkId, GameRolePlayNpcQuestFlag* questFlag) : GameRolePlayNpcInformations(contextualId, look, disposition, npcId, sex, specialArtworkId), questFlag(questFlag)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameRolePlayNpcInformations::Serialize(data);
		questFlag->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayNpcInformations::Deserialize(data);
		questFlag.reset(new GameRolePlayNpcQuestFlag);
		questFlag->Deserialize(data);
	}
};

typedef boost::shared_ptr<GameRolePlayNpcWithQuestInformations> GameRolePlayNpcWithQuestInformationsPtr;

#endif