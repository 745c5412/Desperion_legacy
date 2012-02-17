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

#ifndef __HOUSE_INFORMATIONS_FOR_GUILD__
#define __HOUSE_INFORMATIONS_FOR_GUILD__

class HouseInformationsForGuild : public DofusModel
{
public:
	int houseId;
	int modelId;
	std::string ownerName;
	int16 worldX;
	int16 worldY;
	std::vector<int> skillListIds;
	uint32 guildshareParams;

	uint16 GetProtocol() const
	{ return HOUSE_INFORMATIONS_FOR_GUILD; }

	HouseInformationsForGuild()
	{
	}

	HouseInformationsForGuild(int houseId, int modelId, std::string ownerName, int16 worldX, int16 worldY, std::vector<int>& skillListIds, uint32 guildshareParams) : houseId(houseId), modelId(modelId), ownerName(ownerName), worldX(worldX), worldY(worldY), skillListIds(skillListIds), guildshareParams(guildshareParams)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<houseId<<modelId<<ownerName<<worldX<<worldY;
		uint16 size = skillListIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<skillListIds[a];
		data<<guildshareParams;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>houseId>>modelId>>ownerName>>worldX>>worldY;
		skillListIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			skillListIds.push_back(val);
		}
		data>>guildshareParams;
	}
};

typedef boost::shared_ptr<HouseInformationsForGuild> HouseInformationsForGuildPtr;

#endif