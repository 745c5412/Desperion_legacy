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

#ifndef __PURCHASABLE_DIALOG_MESSAGE__
#define __PURCHASABLE_DIALOG_MESSAGE__

class PurchasableDialogMessage : public DofusMessage
{
public:
	bool buyOrSell;
	int purchasableId;
	int price;

	uint16 GetOpcode() const
	{ return SMSG_PURCHASABLE_DIALOG; }

	PurchasableDialogMessage()
	{
	}

	PurchasableDialogMessage(bool buyOrSell, int purchasableId, int price) : buyOrSell(buyOrSell), purchasableId(purchasableId), price(price)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<buyOrSell<<purchasableId<<price;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>buyOrSell>>purchasableId>>price;
	}
};

#endif