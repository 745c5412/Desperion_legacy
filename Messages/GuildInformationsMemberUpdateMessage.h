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

#ifndef __GUILD_INFORMATIONS_MEMBER_UPDATE_MESSAGE__
#define __GUILD_INFORMATIONS_MEMBER_UPDATE_MESSAGE__

class GuildInformationsMemberUpdateMessage : public DofusMessage
{
public:
	GuildMemberPtr member;

	uint16 GetOpcode() const
	{ return SMSG_GUILD_INFORMATIONS_MEMBER_UPDATE; }

	GuildInformationsMemberUpdateMessage()
	{
	}

	GuildInformationsMemberUpdateMessage(GuildMember* member) : member(member)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		member->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		member.reset(new GuildMember);
		member->Deserialize(data);
	}
};

#endif