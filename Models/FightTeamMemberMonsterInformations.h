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

#ifndef __FIGHT_TEAM_MEMBER_MONSTER_INFORMATIONS__
#define __FIGHT_TEAM_MEMBER_MONSTER_INFORMATIONS__

class FightTeamMemberMonsterInformations : public FightTeamMemberInformations
{
public:
	int monsterId;
	int8 grade;

	uint16 GetProtocol() const
	{ return FIGHT_TEAM_MEMBER_MONSTER_INFORMATIONS; }

	FightTeamMemberMonsterInformations()
	{
	}

	FightTeamMemberMonsterInformations(int id, int monsterId, int8 grade) : FightTeamMemberInformations(id), monsterId(monsterId), grade(grade)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		FightTeamMemberInformations::Serialize(data);
		data<<monsterId<<grade;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightTeamMemberInformations::Deserialize(data);
		data>>monsterId>>grade;
	}
};

typedef boost::shared_ptr<FightTeamMemberMonsterInformations> FightTeamMemberMonsterInformationsPtr;

#endif