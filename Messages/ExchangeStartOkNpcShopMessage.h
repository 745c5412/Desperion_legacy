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

#ifndef __EXCHANGE_START_OK_NPC_SHOP_MESSAGE__
#define __EXCHANGE_START_OK_NPC_SHOP_MESSAGE__

class ExchangeStartOkNpcShopMessage : public DofusMessage
{
public:
	int npcSellerId;
	int tokenId;
	std::vector<ObjectItemToSellInNpcShopPtr> objectsInfos;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_START_OK_NPC_SHOP; }

	ExchangeStartOkNpcShopMessage()
	{
	}

	ExchangeStartOkNpcShopMessage(int npcSellerId, int tokenId, std::vector<ObjectItemToSellInNpcShopPtr>& objectsInfos) : npcSellerId(npcSellerId), tokenId(tokenId), objectsInfos(objectsInfos)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<npcSellerId<<tokenId;
		uint16 size = objectsInfos.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objectsInfos[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>npcSellerId>>tokenId;
		objectsInfos.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemToSellInNpcShopPtr model(new ObjectItemToSellInNpcShop);
			model->Deserialize(data);
			objectsInfos.push_back(model);
		}
	}
};

#endif