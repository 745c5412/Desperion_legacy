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

#ifndef __PADDOCK_TO_SELL_FILTER_MESSAGE__
#define __PADDOCK_TO_SELL_FILTER_MESSAGE__

class PaddockToSellFilterMessage : public DofusMessage
{
public:
	int areaId;
	int8 atLeastNbMount;
	int8 atLeastNbMachine;
	int maxPrice;

	uint16 GetOpcode() const
	{ return CMSG_PADDOCK_TO_SELL_FILTER; }

	PaddockToSellFilterMessage()
	{
	}

	PaddockToSellFilterMessage(int areaId, int8 atLeastNbMount, int8 atLeastNbMachine, int maxPrice) : areaId(areaId), atLeastNbMount(atLeastNbMount), atLeastNbMachine(atLeastNbMachine), maxPrice(maxPrice)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<areaId<<atLeastNbMount<<atLeastNbMachine<<maxPrice;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>areaId>>atLeastNbMount>>atLeastNbMachine>>maxPrice;
	}
};

#endif