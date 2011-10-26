/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

	ObjectItem() : DItem()
	{
	}

	void Init(ByteBuffer& data)
	{
		DItem::Init(data);
		data>>pos>>objectGID>>powerRate>>overMax;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 typeId;
			data>>typeId;
			switch(typeId)
			{
			case OBJECT_EFFECT_INTEGER:
				{
					ObjectEffectPtr obj(new ObjectEffectInteger);
					obj->Init(data);
					effects.push_back(obj);
				}
				break;
			case OBJECT_EFFECT_DICE:
				{
					ObjectEffectPtr obj(new ObjectEffectDice);
					obj->Init(data);
					effects.push_back(obj);
				}
				break;
			case OBJECT_EFFECT:
			default:
				{
					ObjectEffectPtr obj(new ObjectEffect);
					obj->Init(data);
					effects.push_back(obj);
				}
				break;
			}
		}
		data>>objectUID>>quantity;
	}

	void FromThis()
	{
		DItem::FromThis();
		m_buffer<<pos<<objectGID<<powerRate<<overMax; // 0 --> powerRate, false --> overMax
		uint16 size = effects.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			effects[a]->FromThis();
			m_buffer<<effects[a]->GetProtocol()<<*effects[a];
		}
		m_buffer<<objectUID<<quantity;
	}

	ObjectItem(const PlayerItem* item) : DItem()
	{
		m_buffer<<item->GetPos()<<item->GetItem()->GetId()<<uint16(0)<<false; // 0 --> powerRate, false --> overMax
		const std::vector<PlayerItemEffect*>& list = item->GetEffects();
		uint16 size = list.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectEffectPtr e = list[a]->ToObjectEffect();
			m_buffer<<e->GetProtocol()<<*e;
		}
		m_buffer<<item->GetGuid()<<item->GetQuantity();
	}
};

#endif