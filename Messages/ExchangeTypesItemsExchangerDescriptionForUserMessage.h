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

#ifndef __EXCHANGE_TYPES_ITEMS_EXCHANGER_DESCRIPTION_FOR_USER_MESSAGE__
#define __EXCHANGE_TYPES_ITEMS_EXCHANGER_DESCRIPTION_FOR_USER_MESSAGE__

class ExchangeTypesItemsExchangerDescriptionForUserMessage : public DofusMessage
{
public:
	std::vector<BidExchangerObjectInfoPtr> itemTypeDescriptions;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_TYPES_ITEMS_EXCHANGER_DESCRIPTION_FOR_USER; }

	ExchangeTypesItemsExchangerDescriptionForUserMessage()
	{
	}

	ExchangeTypesItemsExchangerDescriptionForUserMessage(std::vector<BidExchangerObjectInfoPtr>& itemTypeDescriptions) : itemTypeDescriptions(itemTypeDescriptions)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = itemTypeDescriptions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			itemTypeDescriptions[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		itemTypeDescriptions.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			BidExchangerObjectInfoPtr model(new BidExchangerObjectInfo);
			model->Deserialize(data);
			itemTypeDescriptions.push_back(model);
		}
	}
};

#endif