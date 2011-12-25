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

#ifndef __GUILD_INFORMATIONS__
#define __GUILD_INFORMATIONS__

class GuildInformations : public BasicGuildInformations
{
public:
	GuildEmblemPtr guildEmblem;

	uint16 GetProtocol() const
	{ return GUILD_INFORMATIONS; }

	GuildInformations()
	{
	}

	GuildInformations(int guildId, std::string guildName, GuildEmblem* guildEmblem) : BasicGuildInformations(guildId, guildName), guildEmblem(guildEmblem)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		BasicGuildInformations::Serialize(data);
		guildEmblem->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		BasicGuildInformations::Deserialize(data);
		guildEmblem.reset(new GuildEmblem);
		guildEmblem->Deserialize(data);
	}
};

typedef boost::shared_ptr<GuildInformations> GuildInformationsPtr;

#endif