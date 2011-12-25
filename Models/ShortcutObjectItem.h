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

#ifndef __SHORTCUT_OBJECT_ITEM__
#define __SHORTCUT_OBJECT_ITEM__

class ShortcutObjectItem : public ShortcutObject
{
public:
	int itemUID;
	int itemGID;

	uint16 GetProtocol() const
	{ return SHORTCUT_OBJECT_ITEM; }

	ShortcutObjectItem()
	{
	}

	ShortcutObjectItem(int8 error, int itemUID, int itemGID) : ShortcutObject(error), itemUID(itemUID), itemGID(itemGID)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ShortcutObject::Serialize(data);
		data<<itemUID<<itemGID;
	}

	void Deserialize(ByteBuffer& data)
	{
		ShortcutObject::Deserialize(data);
		data>>itemUID>>itemGID;
	}
};

typedef boost::shared_ptr<ShortcutObjectItem> ShortcutObjectItemPtr;

#endif