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

#ifndef __OBJECT_ITEM_TO_SELL_IN_HUMAN_VENDOR_SHOP__
#define __OBJECT_ITEM_TO_SELL_IN_HUMAN_VENDOR_SHOP__

class ObjectItemToSellInHumanVendorShop : public DItem
{
public:
	int16 objectGID;
	int16 powerRate;
	bool overMax;
	std::vector<ObjectEffectPtr> effects;
	int objectUID;
	int quantity;
	int objectPrice;
	int publicPrice;

	uint16 GetProtocol() const
	{ return OBJECT_ITEM_TO_SELL_IN_HUMAN_VENDOR_SHOP; }

	ObjectItemToSellInHumanVendorShop()
	{
	}

	ObjectItemToSellInHumanVendorShop(int16 objectGID, int16 powerRate, bool overMax, std::vector<ObjectEffectPtr>& effects, int objectUID, int quantity, int objectPrice, int publicPrice) : DItem(), objectGID(objectGID), powerRate(powerRate), overMax(overMax), effects(effects), objectUID(objectUID), quantity(quantity), objectPrice(objectPrice), publicPrice(publicPrice)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		DItem::Serialize(data);
		data<<objectGID<<powerRate<<overMax;
		uint16 size = effects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<effects[a]->GetProtocol();
			effects[a]->Serialize(data);
		}
		data<<objectUID<<quantity<<objectPrice<<publicPrice;
	}

	void Deserialize(ByteBuffer& data)
	{
		DItem::Deserialize(data);
		data>>objectGID>>powerRate>>overMax;
		effects.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			ObjectEffectPtr model(Desperion::ProtocolTypeManager::GetObjectEffect(protocol));
			model->Deserialize(data);
			effects.push_back(model);
		}
		data>>objectUID>>quantity>>objectPrice>>publicPrice;
	}
};

typedef boost::shared_ptr<ObjectItemToSellInHumanVendorShop> ObjectItemToSellInHumanVendorShopPtr;

#endif