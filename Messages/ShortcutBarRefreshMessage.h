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

#ifndef __SHORTCUT_BAR_REFRESH_MESSAGE__
#define __SHORTCUT_BAR_REFRESH_MESSAGE__

class ShortcutBarRefreshMessage : public DofusMessage
{
public:
	int8 barType;
	ShortcutPtr shortcut;

	uint16 GetOpcode() const
	{ return SMSG_SHORTCUT_BAR_REFRESH; }

	ShortcutBarRefreshMessage()
	{
	}

	ShortcutBarRefreshMessage(int8 barType, Shortcut* shortcut) : barType(barType), shortcut(shortcut)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<barType<<shortcut->GetProtocol();
		shortcut->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>barType;
		uint16 protocol;
		data>>protocol;
		shortcut.reset(Desperion::ProtocolTypeManager::GetShortcut(protocol));
		shortcut->Deserialize(data);
	}
};

#endif