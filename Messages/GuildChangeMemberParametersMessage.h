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

#ifndef __GUILD_CHANGE_MEMBER_PARAMETERS_MESSAGE__
#define __GUILD_CHANGE_MEMBER_PARAMETERS_MESSAGE__

class GuildChangeMemberParametersMessage : public DofusMessage
{
public:
	int memberId;
	int16 rank;
	int8 experienceGivenPercent;
	uint32 rights;

	uint16 GetOpcode() const
	{ return CMSG_GUILD_CHANGE_MEMBER_PARAMETERS; }

	GuildChangeMemberParametersMessage()
	{
	}

	GuildChangeMemberParametersMessage(int memberId, int16 rank, int8 experienceGivenPercent, uint32 rights) : memberId(memberId), rank(rank), experienceGivenPercent(experienceGivenPercent), rights(rights)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<memberId<<rank<<experienceGivenPercent<<rights;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>memberId>>rank>>experienceGivenPercent>>rights;
	}
};

#endif