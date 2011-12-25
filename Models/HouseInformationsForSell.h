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

#ifndef __HOUSE_INFORMATIONS_FOR_SELL__
#define __HOUSE_INFORMATIONS_FOR_SELL__

class HouseInformationsForSell : public DofusModel
{
public:
	int modelId;
	std::string ownerName;
	bool ownerConnected;
	int16 worldX;
	int16 worldY;
	int16 subAreaId;
	int8 nbRoom;
	int8 nbChest;
	std::vector<int> skillListIds;
	bool isLocked;
	int price;

	uint16 GetProtocol() const
	{ return HOUSE_INFORMATIONS_FOR_SELL; }

	HouseInformationsForSell()
	{
	}

	HouseInformationsForSell(int modelId, std::string ownerName, bool ownerConnected, int16 worldX, int16 worldY, int16 subAreaId, int8 nbRoom, int8 nbChest, std::vector<int>& skillListIds, bool isLocked, int price) : modelId(modelId), ownerName(ownerName), ownerConnected(ownerConnected), worldX(worldX), worldY(worldY), subAreaId(subAreaId), nbRoom(nbRoom), nbChest(nbChest), skillListIds(skillListIds), isLocked(isLocked), price(price)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<modelId<<ownerName<<ownerConnected<<worldX<<worldY<<subAreaId<<nbRoom<<nbChest;
		uint16 size = skillListIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<skillListIds[a];
		data<<isLocked<<price;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>modelId>>ownerName>>ownerConnected>>worldX>>worldY>>subAreaId>>nbRoom>>nbChest;
		skillListIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			skillListIds.push_back(val);
		}
		data>>isLocked>>price;
	}
};

typedef boost::shared_ptr<HouseInformationsForSell> HouseInformationsForSellPtr;

#endif