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

#ifndef __FIGHT_TEAM_LIGHT_INFORMATIONS__
#define __FIGHT_TEAM_LIGHT_INFORMATIONS__

class FightTeamLightInformations : public AbstractFightTeamInformations
{
public:
	int8 teamMembersCount;

	uint16 GetProtocol() const
	{ return FIGHT_TEAM_LIGHT_INFORMATIONS; }

	FightTeamLightInformations()
	{
	}

	FightTeamLightInformations(int8 teamId, int leaderId, int8 teamSide, int8 teamTypeId, int8 teamMembersCount) : AbstractFightTeamInformations(teamId, leaderId, teamSide, teamTypeId), teamMembersCount(teamMembersCount)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractFightTeamInformations::Serialize(data);
		data<<teamMembersCount;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractFightTeamInformations::Deserialize(data);
		data>>teamMembersCount;
	}
};

typedef boost::shared_ptr<FightTeamLightInformations> FightTeamLightInformationsPtr;

#endif