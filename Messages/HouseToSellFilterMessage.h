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

#ifndef __HOUSE_TO_SELL_FILTER_MESSAGE__
#define __HOUSE_TO_SELL_FILTER_MESSAGE__

class HouseToSellFilterMessage : public DofusMessage
{
public:
	int areaId;
	int8 atLeastNbRoom;
	int8 atLeastNbChest;
	int8 skillRequested;
	int maxPrice;

	uint16 GetOpcode() const
	{ return CMSG_HOUSE_TO_SELL_FILTER; }

	HouseToSellFilterMessage()
	{
	}

	HouseToSellFilterMessage(int areaId, int8 atLeastNbRoom, int8 atLeastNbChest, int8 skillRequested, int maxPrice) : areaId(areaId), atLeastNbRoom(atLeastNbRoom), atLeastNbChest(atLeastNbChest), skillRequested(skillRequested), maxPrice(maxPrice)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<areaId<<atLeastNbRoom<<atLeastNbChest<<skillRequested<<maxPrice;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>areaId>>atLeastNbRoom>>atLeastNbChest>>skillRequested>>maxPrice;
	}
};

#endif