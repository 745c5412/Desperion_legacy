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

#ifndef __SHORTCUT_OBJECT_PRESET__
#define __SHORTCUT_OBJECT_PRESET__

class ShortcutObjectPreset : public ShortcutObject
{
public:
	int8 presetId;

	uint16 GetProtocol() const
	{ return SHORTCUT_OBJECT_PRESET; }

	ShortcutObjectPreset()
	{
	}

	ShortcutObjectPreset(int8 error, int8 presetId) : ShortcutObject(error), presetId(presetId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ShortcutObject::Serialize(data);
		data<<presetId;
	}

	void Deserialize(ByteBuffer& data)
	{
		ShortcutObject::Deserialize(data);
		data>>presetId;
	}
};

typedef boost::shared_ptr<ShortcutObjectPreset> ShortcutObjectPresetPtr;

#endif