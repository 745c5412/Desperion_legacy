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

#ifndef __GAME_ROLE_PLAY_MUTANT_INFORMATIONS__
#define __GAME_ROLE_PLAY_MUTANT_INFORMATIONS__

class GameRolePlayMutantInformations : public GameRolePlayHumanoidInformations
{
public:
	int monsterId;
	int8 powerLevel;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_MUTANT_INFORMATIONS; }

	GameRolePlayMutantInformations()
	{
	}

	GameRolePlayMutantInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name, HumanInformations* humanoidInfo, int monsterId, int8 powerLevel) : GameRolePlayHumanoidInformations(contextualId, look, disposition, name, humanoidInfo), monsterId(monsterId), powerLevel(powerLevel)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameRolePlayHumanoidInformations::Serialize(data);
		data<<monsterId<<powerLevel;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayHumanoidInformations::Deserialize(data);
		data>>monsterId>>powerLevel;
	}
};

typedef boost::shared_ptr<GameRolePlayMutantInformations> GameRolePlayMutantInformationsPtr;

#endif