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

#ifndef __ABSTRACT_FIGHT_TEAM_INFORMATIONS__
#define __ABSTRACT_FIGHT_TEAM_INFORMATIONS__

class AbstractFightTeamInformations : public DofusModel
{
public:
	int8 teamId;
	int leaderId;
	int8 teamSide;
	int8 teamTypeId;

	uint16 GetProtocol() const
	{ return ABSTRACT_FIGHT_TEAM_INFORMATIONS; }

	AbstractFightTeamInformations()
	{
	}

	AbstractFightTeamInformations(int8 teamId, int leaderId, int8 teamSide, int8 teamTypeId) : teamId(teamId), leaderId(leaderId), teamSide(teamSide), teamTypeId(teamTypeId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<teamId<<leaderId<<teamSide<<teamTypeId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>teamId>>leaderId>>teamSide>>teamTypeId;
	}
};

typedef boost::shared_ptr<AbstractFightTeamInformations> AbstractFightTeamInformationsPtr;

#endif