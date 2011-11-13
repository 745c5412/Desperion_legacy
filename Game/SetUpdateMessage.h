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

#ifndef __SET_UPDATE_MESSAGE__
#define __SET_UPDATE_MESSAGE__

class SetUpdateMessage : public DofusMessage
{
public:
	int16 setId;
	std::vector<int16> setObjects;
	std::vector<ObjectEffectPtr> setEffects;

	virtual uint16 GetOpcode() const
	{ return SMSG_SET_UPDATE; }

	SetUpdateMessage(int16 setId, std::vector<int16>& setObjects, const std::vector<EffectInstance*>& setEffects)
		: setId(setId), setObjects(setObjects)
	{
		for(std::vector<EffectInstance*>::const_iterator it = setEffects.begin(); it != setEffects.end(); ++it)
		{
			ObjectEffectPtr obj((*it)->ToPlayerItemEffect()->ToObjectEffect());
			this->setEffects.push_back(obj);
		}
	}

	void Serialize(ByteBuffer& data)
	{
		data<<setId;
		uint16 size = setObjects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<setObjects[a];
		size = setEffects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<setEffects[a]->GetProtocol();
			setEffects[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		setObjects.clear();
		setEffects.clear();
		data>>setId;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 obj;
			data>>obj;
			setObjects.push_back(obj);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			ObjectEffectPtr obj(Desperion::ProtocolTypeManager::GetObjectEffect(protocol));
			obj->Deserialize(data);
			setEffects.push_back(obj);
		}
	}
};

#endif