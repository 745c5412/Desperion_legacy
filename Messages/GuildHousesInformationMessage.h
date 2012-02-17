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

#ifndef __GUILD_HOUSES_INFORMATION_MESSAGE__
#define __GUILD_HOUSES_INFORMATION_MESSAGE__

class GuildHousesInformationMessage : public DofusMessage
{
public:
	std::vector<HouseInformationsForGuildPtr> housesInformations;

	uint16 GetOpcode() const
	{ return SMSG_GUILD_HOUSES_INFORMATION; }

	GuildHousesInformationMessage()
	{
	}

	GuildHousesInformationMessage(std::vector<HouseInformationsForGuildPtr>& housesInformations) : housesInformations(housesInformations)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = housesInformations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			housesInformations[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		housesInformations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			HouseInformationsForGuildPtr model(new HouseInformationsForGuild);
			model->Deserialize(data);
			housesInformations.push_back(model);
		}
	}
};

#endif