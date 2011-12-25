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

#ifndef __HOUSE_TO_SELL_LIST_MESSAGE__
#define __HOUSE_TO_SELL_LIST_MESSAGE__

class HouseToSellListMessage : public DofusMessage
{
public:
	int16 pageIndex;
	int16 totalPage;
	std::vector<HouseInformationsForSellPtr> houseList;

	uint16 GetOpcode() const
	{ return SMSG_HOUSE_TO_SELL_LIST; }

	HouseToSellListMessage()
	{
	}

	HouseToSellListMessage(int16 pageIndex, int16 totalPage, std::vector<HouseInformationsForSellPtr>& houseList) : pageIndex(pageIndex), totalPage(totalPage), houseList(houseList)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<pageIndex<<totalPage;
		uint16 size = houseList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			houseList[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>pageIndex>>totalPage;
		houseList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			HouseInformationsForSellPtr model(new HouseInformationsForSell);
			model->Deserialize(data);
			houseList.push_back(model);
		}
	}
};

#endif