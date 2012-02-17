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

#ifndef __HOUSE_SOLD_MESSAGE__
#define __HOUSE_SOLD_MESSAGE__

class HouseSoldMessage : public DofusMessage
{
public:
	int houseId;
	int realPrice;
	std::string buyerName;

	uint16 GetOpcode() const
	{ return SMSG_HOUSE_SOLD; }

	HouseSoldMessage()
	{
	}

	HouseSoldMessage(int houseId, int realPrice, std::string buyerName) : houseId(houseId), realPrice(realPrice), buyerName(buyerName)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<houseId<<realPrice<<buyerName;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>houseId>>realPrice>>buyerName;
	}
};

#endif