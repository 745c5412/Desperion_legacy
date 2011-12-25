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

#ifndef __GAME_FIGHT_MONSTER_WITH_ALIGNMENT_INFORMATIONS__
#define __GAME_FIGHT_MONSTER_WITH_ALIGNMENT_INFORMATIONS__

class GameFightMonsterWithAlignmentInformations : public GameFightMonsterInformations
{
public:
	ActorAlignmentInformationsPtr alignmentInfos;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_MONSTER_WITH_ALIGNMENT_INFORMATIONS; }

	GameFightMonsterWithAlignmentInformations()
	{
	}

	GameFightMonsterWithAlignmentInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int8 teamId, bool alive, GameFightMinimalStats* stats, int16 creatureGenericId, int8 creatureGrade, ActorAlignmentInformations* alignmentInfos) : GameFightMonsterInformations(contextualId, look, disposition, teamId, alive, stats, creatureGenericId, creatureGrade), alignmentInfos(alignmentInfos)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameFightMonsterInformations::Serialize(data);
		alignmentInfos->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightMonsterInformations::Deserialize(data);
		alignmentInfos.reset(new ActorAlignmentInformations);
		alignmentInfos->Deserialize(data);
	}
};

typedef boost::shared_ptr<GameFightMonsterWithAlignmentInformations> GameFightMonsterWithAlignmentInformationsPtr;

#endif