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

#ifndef __GAME_ROLE_PLAY_GROUP_MONSTER_INFORMATIONS__
#define __GAME_ROLE_PLAY_GROUP_MONSTER_INFORMATIONS__

class GameRolePlayGroupMonsterInformations : public GameRolePlayActorInformations
{
public:
	int mainCreatureGenericId;
	int8 mainCreatureGrade;
	std::vector<MonsterInGroupInformationsPtr> underlings;
	int16 ageBonus;
	int8 alignmentSide;
	bool keyRingBonus;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_GROUP_MONSTER_INFORMATIONS; }

	GameRolePlayGroupMonsterInformations()
	{
	}

	GameRolePlayGroupMonsterInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int mainCreatureGenericId, int8 mainCreatureGrade, std::vector<MonsterInGroupInformationsPtr>& underlings, int16 ageBonus, int8 alignmentSide, bool keyRingBonus) : GameRolePlayActorInformations(contextualId, look, disposition), mainCreatureGenericId(mainCreatureGenericId), mainCreatureGrade(mainCreatureGrade), underlings(underlings), ageBonus(ageBonus), alignmentSide(alignmentSide), keyRingBonus(keyRingBonus)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameRolePlayActorInformations::Serialize(data);
		data<<mainCreatureGenericId<<mainCreatureGrade;
		uint16 size = underlings.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			underlings[a]->Serialize(data);
		data<<ageBonus<<alignmentSide<<keyRingBonus;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Deserialize(data);
		data>>mainCreatureGenericId>>mainCreatureGrade;
		underlings.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MonsterInGroupInformationsPtr model(new MonsterInGroupInformations);
			model->Deserialize(data);
			underlings.push_back(model);
		}
		data>>ageBonus>>alignmentSide>>keyRingBonus;
	}
};

typedef boost::shared_ptr<GameRolePlayGroupMonsterInformations> GameRolePlayGroupMonsterInformationsPtr;

#endif