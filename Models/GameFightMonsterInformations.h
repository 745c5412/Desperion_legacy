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

#ifndef __GAME_FIGHT_MONSTER_INFORMATIONS__
#define __GAME_FIGHT_MONSTER_INFORMATIONS__

class GameFightMonsterInformations : public GameFightAIInformations
{
public:
	int16 creatureGenericId;
	int8 creatureGrade;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_MONSTER_INFORMATIONS; }

	GameFightMonsterInformations()
	{
	}

	GameFightMonsterInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int8 teamId, bool alive, GameFightMinimalStats* stats, int16 creatureGenericId, int8 creatureGrade) : GameFightAIInformations(contextualId, look, disposition, teamId, alive, stats), creatureGenericId(creatureGenericId), creatureGrade(creatureGrade)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameFightAIInformations::Serialize(data);
		data<<creatureGenericId<<creatureGrade;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightAIInformations::Deserialize(data);
		data>>creatureGenericId>>creatureGrade;
	}
};

typedef boost::shared_ptr<GameFightMonsterInformations> GameFightMonsterInformationsPtr;

#endif