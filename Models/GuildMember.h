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

#ifndef __GUILD_MEMBER__
#define __GUILD_MEMBER__

class GuildMember : public CharacterMinimalInformations
{
public:
	int8 breed;
	bool sex;
	int16 rank;
	int64 givenExperience;
	int8 experienceGivenPercent;
	uint32 rights;
	int8 connected;
	int8 alignmentSide;
	uint16 hoursSinceLastConnection;
	int8 moodSmileyId;

	uint16 GetProtocol() const
	{ return GUILD_MEMBER; }

	GuildMember()
	{
	}

	GuildMember(int id, uint8 level, std::string name, int8 breed, bool sex, int16 rank, int64 givenExperience, int8 experienceGivenPercent, uint32 rights, int8 connected, int8 alignmentSide, uint16 hoursSinceLastConnection, int8 moodSmileyId) : CharacterMinimalInformations(id, level, name), breed(breed), sex(sex), rank(rank), givenExperience(givenExperience), experienceGivenPercent(experienceGivenPercent), rights(rights), connected(connected), alignmentSide(alignmentSide), hoursSinceLastConnection(hoursSinceLastConnection), moodSmileyId(moodSmileyId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterMinimalInformations::Serialize(data);
		data<<breed<<sex<<rank<<givenExperience<<experienceGivenPercent<<rights<<connected<<alignmentSide<<hoursSinceLastConnection<<moodSmileyId;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterMinimalInformations::Deserialize(data);
		data>>breed>>sex>>rank>>givenExperience>>experienceGivenPercent>>rights>>connected>>alignmentSide>>hoursSinceLastConnection>>moodSmileyId;
	}
};

typedef boost::shared_ptr<GuildMember> GuildMemberPtr;

#endif