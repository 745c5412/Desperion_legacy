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

#ifndef __OBJECT_ITEM__
#define __OBJECT_ITEM__

class ObjectItem : public DItem
{
public:
	uint8 pos;
	int16 objectGID;
	int16 powerRate;
	bool overMax;
	std::vector<ObjectEffectPtr> effects;
	int objectUID;
	int quantity;

	virtual uint16 GetProtocol() const
	{ return OBJECT_ITEM; }

	ObjectItem()
	{
	}

	ObjectItem(const PlayerItem* item) : pos(item->GetPos()), objectGID(item->GetItem()->GetId()), 
		powerRate(0), overMax(false), objectUID(item->GetGuid()), quantity(item->GetQuantity())
	{
		const std::vector<PlayerItemEffect*>& list = item->GetEffects();
		for(uint16 a = 0; a < list.size(); ++a)
		{
			ObjectEffectPtr e = list[a]->ToObjectEffect();
			effects.push_back(e);
		}
	}

	void Serialize(ByteBuffer& data)
	{
		DItem::Serialize(data);
		data<<pos<<objectGID<<powerRate<<overMax; // 0 --> powerRate, false --> overMax
		uint16 size = effects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<effects[a]->GetProtocol();
			effects[a]->Serialize(data);
		}
		data<<objectUID<<quantity;
	}

	void Deserialize(ByteBuffer& data)
	{
		effects.clear();
		DItem::Deserialize(data);
		data>>pos>>objectGID>>powerRate>>overMax;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 typeId;
			data>>typeId;
			ObjectEffectPtr effect(Desperion::ProtocolTypeManager::GetObjectEffect(typeId));
			effect->Deserialize(data);
			effects.push_back(effect);
		}
		data>>objectUID>>quantity;
	}
};

typedef boost::shared_ptr<ObjectItem> ObjectItemPtr;

#endif