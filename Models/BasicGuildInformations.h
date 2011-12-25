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

#ifndef __BASIC_GUILD_INFORMATIONS__
#define __BASIC_GUILD_INFORMATIONS__

class BasicGuildInformations : public DofusModel
{
public:
	int guildId;
	std::string guildName;

	uint16 GetProtocol() const
	{ return BASIC_GUILD_INFORMATIONS; }

	BasicGuildInformations()
	{
	}

	BasicGuildInformations(int guildId, std::string guildName) : guildId(guildId), guildName(guildName)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<guildId<<guildName;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>guildId>>guildName;
	}
};

typedef boost::shared_ptr<BasicGuildInformations> BasicGuildInformationsPtr;

#endif