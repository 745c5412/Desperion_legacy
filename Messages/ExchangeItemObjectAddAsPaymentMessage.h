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

#ifndef __EXCHANGE_ITEM_OBJECT_ADD_AS_PAYMENT_MESSAGE__
#define __EXCHANGE_ITEM_OBJECT_ADD_AS_PAYMENT_MESSAGE__

class ExchangeItemObjectAddAsPaymentMessage : public DofusMessage
{
public:
	int8 paymentType;
	bool bAdd;
	int objectToMoveId;
	int quantity;

	uint16 GetOpcode() const
	{ return CMSG_EXCHANGE_ITEM_OBJECT_ADD_AS_PAYMENT; }

	ExchangeItemObjectAddAsPaymentMessage()
	{
	}

	ExchangeItemObjectAddAsPaymentMessage(int8 paymentType, bool bAdd, int objectToMoveId, int quantity) : paymentType(paymentType), bAdd(bAdd), objectToMoveId(objectToMoveId), quantity(quantity)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<paymentType<<bAdd<<objectToMoveId<<quantity;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>paymentType>>bAdd>>objectToMoveId>>quantity;
	}
};

#endif