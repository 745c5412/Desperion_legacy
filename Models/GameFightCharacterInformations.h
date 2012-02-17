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

#ifndef __GAME_FIGHT_CHARACTER_INFORMATIONS__
#define __GAME_FIGHT_CHARACTER_INFORMATIONS__

class GameFightCharacterInformations : public GameFightFighterNamedInformations
{
public:
	int16 level;
	ActorAlignmentInformationsPtr alignmentInfos;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_CHARACTER_INFORMATIONS; }

	GameFightCharacterInformations()
	{
	}

	GameFightCharacterInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int8 teamId, bool alive, GameFightMinimalStats* stats, std::string name, int16 level, ActorAlignmentInformations* alignmentInfos) : GameFightFighterNamedInformations(contextualId, look, disposition, teamId, alive, stats, name), level(level), alignmentInfos(alignmentInfos)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameFightFighterNamedInformations::Serialize(data);
		data<<level;
		alignmentInfos->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightFighterNamedInformations::Deserialize(data);
		data>>level;
		alignmentInfos.reset(new ActorAlignmentInformations);
		alignmentInfos->Deserialize(data);
	}
};

typedef boost::shared_ptr<GameFightCharacterInformations> GameFightCharacterInformationsPtr;

#endif