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

#ifndef __EXCHANGE_SHOP_STOCK_MOVEMENT_UPDATED_MESSAGE__
#define __EXCHANGE_SHOP_STOCK_MOVEMENT_UPDATED_MESSAGE__

class ExchangeShopStockMovementUpdatedMessage : public DofusMessage
{
public:
	ObjectItemToSellPtr objectInfo;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_SHOP_STOCK_MOVEMENT_UPDATED; }

	ExchangeShopStockMovementUpdatedMessage()
	{
	}

	ExchangeShopStockMovementUpdatedMessage(ObjectItemToSell* objectInfo) : objectInfo(objectInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		objectInfo->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		objectInfo.reset(new ObjectItemToSell);
		objectInfo->Deserialize(data);
	}
};

#endif