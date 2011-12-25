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

#ifndef __HUMAN_WITH_GUILD_INFORMATIONS__
#define __HUMAN_WITH_GUILD_INFORMATIONS__

class HumanWithGuildInformations : public HumanInformations
{
public:
	GuildInformationsPtr guildInformations;

	uint16 GetProtocol() const
	{ return HUMAN_WITH_GUILD_INFORMATIONS; }

	HumanWithGuildInformations()
	{
	}

	HumanWithGuildInformations(std::vector<EntityLookPtr>& followingCharactersLook, int8 emoteId, int64 emoteStartTime, ActorRestrictionsInformations* restrictions, int16 titleId, std::string titleParam, GuildInformations* guildInformations) : HumanInformations(followingCharactersLook, emoteId, emoteStartTime, restrictions, titleId, titleParam), guildInformations(guildInformations)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		HumanInformations::Serialize(data);
		guildInformations->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		HumanInformations::Deserialize(data);
		guildInformations.reset(new GuildInformations);
		guildInformations->Deserialize(data);
	}
};

typedef boost::shared_ptr<HumanWithGuildInformations> HumanWithGuildInformationsPtr;

#endif