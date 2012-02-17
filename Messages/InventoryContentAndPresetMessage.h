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

#ifndef __INVENTORY_CONTENT_AND_PRESET_MESSAGE__
#define __INVENTORY_CONTENT_AND_PRESET_MESSAGE__

class InventoryContentAndPresetMessage : public InventoryContentMessage
{
public:
	std::vector<PresetPtr> presets;

	uint16 GetOpcode() const
	{ return SMSG_INVENTORY_CONTENT_AND_PRESET; }

	InventoryContentAndPresetMessage()
	{
	}

	InventoryContentAndPresetMessage(std::vector<ObjectItemPtr>& objects, int kamas, std::vector<PresetPtr>& presets) : InventoryContentMessage(objects, kamas), presets(presets)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		InventoryContentMessage::Serialize(data);
		uint16 size = presets.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			presets[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		InventoryContentMessage::Deserialize(data);
		presets.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PresetPtr model(new Preset);
			model->Deserialize(data);
			presets.push_back(model);
		}
	}
};

#endif