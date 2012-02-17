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

#ifndef __PRESET__
#define __PRESET__

class Preset : public DofusModel
{
public:
	int8 presetId;
	int8 symbolId;
	bool mount;
	std::vector<PresetItemPtr> objects;

	uint16 GetProtocol() const
	{ return PRESET; }

	Preset()
	{
	}

	Preset(int8 presetId, int8 symbolId, bool mount, std::vector<PresetItemPtr>& objects) : presetId(presetId), symbolId(symbolId), mount(mount), objects(objects)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<presetId<<symbolId<<mount;
		uint16 size = objects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objects[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>presetId>>symbolId>>mount;
		objects.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PresetItemPtr model(new PresetItem);
			model->Deserialize(data);
			objects.push_back(model);
		}
	}
};

typedef boost::shared_ptr<Preset> PresetPtr;

#endif