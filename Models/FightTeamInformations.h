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

#ifndef __FIGHT_TEAM_INFORMATIONS__
#define __FIGHT_TEAM_INFORMATIONS__

class FightTeamInformations : public AbstractFightTeamInformations
{
public:
	std::vector<FightTeamMemberInformationsPtr> teamMembers;

	uint16 GetProtocol() const
	{ return FIGHT_TEAM_INFORMATIONS; }

	FightTeamInformations()
	{
	}

	FightTeamInformations(int8 teamId, int leaderId, int8 teamSide, int8 teamTypeId, std::vector<FightTeamMemberInformationsPtr>& teamMembers) : AbstractFightTeamInformations(teamId, leaderId, teamSide, teamTypeId), teamMembers(teamMembers)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractFightTeamInformations::Serialize(data);
		uint16 size = teamMembers.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<teamMembers[a]->GetProtocol();
			teamMembers[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractFightTeamInformations::Deserialize(data);
		teamMembers.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FightTeamMemberInformationsPtr model(Desperion::ProtocolTypeManager::GetFightTeamMemberInformations(protocol));
			model->Deserialize(data);
			teamMembers.push_back(model);
		}
	}
};

typedef boost::shared_ptr<FightTeamInformations> FightTeamInformationsPtr;

#endif