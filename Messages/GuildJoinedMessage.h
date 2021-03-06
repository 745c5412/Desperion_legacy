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

#ifndef __GUILD_JOINED_MESSAGE__
#define __GUILD_JOINED_MESSAGE__

class GuildJoinedMessage : public DofusMessage
{
public:
	GuildInformationsPtr guildInfo;
	uint32 memberRights;

	uint16 GetOpcode() const
	{ return SMSG_GUILD_JOINED; }

	GuildJoinedMessage()
	{
	}

	GuildJoinedMessage(GuildInformations* guildInfo, uint32 memberRights) : guildInfo(guildInfo), memberRights(memberRights)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		guildInfo->Serialize(data);
		data<<memberRights;
	}

	void Deserialize(ByteBuffer& data)
	{
		guildInfo.reset(new GuildInformations);
		guildInfo->Deserialize(data);
		data>>memberRights;
	}
};

#endif