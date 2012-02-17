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

#ifndef __OBJECT_ITEM_TO_SELL_IN_NPC_SHOP__
#define __OBJECT_ITEM_TO_SELL_IN_NPC_SHOP__

class ObjectItemToSellInNpcShop : public ObjectItemMinimalInformation
{
public:
	int objectPrice;
	std::string buyCriterion;

	uint16 GetProtocol() const
	{ return OBJECT_ITEM_TO_SELL_IN_NPC_SHOP; }

	ObjectItemToSellInNpcShop()
	{
	}

	ObjectItemToSellInNpcShop(int16 objectGID, int16 powerRate, bool overMax, std::vector<ObjectEffectPtr>& effects, int objectPrice, std::string buyCriterion) : ObjectItemMinimalInformation(objectGID, powerRate, overMax, effects), objectPrice(objectPrice), buyCriterion(buyCriterion)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		ObjectItemMinimalInformation::Serialize(data);
		data<<objectPrice<<buyCriterion;
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectItemMinimalInformation::Deserialize(data);
		data>>objectPrice>>buyCriterion;
	}
};

typedef boost::shared_ptr<ObjectItemToSellInNpcShop> ObjectItemToSellInNpcShopPtr;

#endif