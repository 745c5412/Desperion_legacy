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

#ifndef __OBJECT_ITEM_MINIMAL_INFORMATION__
#define __OBJECT_ITEM_MINIMAL_INFORMATION__

class ObjectItemMinimalInformation : public DItem
{
public:
	int16 objectGID;
	int16 powerRate;
	bool overMax;
	std::vector<ObjectEffectPtr> effects;

	uint16 GetProtocol() const
	{ return OBJECT_ITEM_MINIMAL_INFORMATION; }

	ObjectItemMinimalInformation()
	{
	}

	ObjectItemMinimalInformation(int16 objectGID, int16 powerRate, bool overMax, std::vector<ObjectEffectPtr>& effects) : DItem(), objectGID(objectGID), powerRate(powerRate), overMax(overMax), effects(effects)
	{
	}

	void Serialize(ByteBuffer& data)
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
	}
};

typedef boost::shared_ptr<ObjectItemMinimalInformation> ObjectItemMinimalInformationPtr;

#endif