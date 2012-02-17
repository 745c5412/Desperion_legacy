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

#ifndef __FIGHT_TEAM_MEMBER_TAX_COLLECTOR_INFORMATIONS__
#define __FIGHT_TEAM_MEMBER_TAX_COLLECTOR_INFORMATIONS__

class FightTeamMemberTaxCollectorInformations : public FightTeamMemberInformations
{
public:
	int16 firstNameId;
	int16 lastNameId;
	uint8 level;
	int guildId;
	int uid;

	uint16 GetProtocol() const
	{ return FIGHT_TEAM_MEMBER_TAX_COLLECTOR_INFORMATIONS; }

	FightTeamMemberTaxCollectorInformations()
	{
	}

	FightTeamMemberTaxCollectorInformations(int id, int16 firstNameId, int16 lastNameId, uint8 level, int guildId, int uid) : FightTeamMemberInformations(id), firstNameId(firstNameId), lastNameId(lastNameId), level(level), guildId(guildId), uid(uid)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FightTeamMemberInformations::Serialize(data);
		data<<firstNameId<<lastNameId<<level<<guildId<<uid;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightTeamMemberInformations::Deserialize(data);
		data>>firstNameId>>lastNameId>>level>>guildId>>uid;
	}
};

typedef boost::shared_ptr<FightTeamMemberTaxCollectorInformations> FightTeamMemberTaxCollectorInformationsPtr;

#endif