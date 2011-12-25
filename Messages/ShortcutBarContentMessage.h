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

#ifndef __SHORTCUT_BAR_CONTENT_MESSAGE__
#define __SHORTCUT_BAR_CONTENT_MESSAGE__

class ShortcutBarContentMessage : public DofusMessage
{
public:
	int8 barType;
	std::vector<ShortcutPtr> shortcuts;

	uint16 GetOpcode() const
	{ return SMSG_SHORTCUT_BAR_CONTENT; }

	ShortcutBarContentMessage()
	{
	}

	ShortcutBarContentMessage(int8 barType, std::vector<ShortcutPtr>& shortcuts) : barType(barType), shortcuts(shortcuts)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<barType;
		uint16 size = shortcuts.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<shortcuts[a]->GetProtocol();
			shortcuts[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>barType;
		shortcuts.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			ShortcutPtr model(Desperion::ProtocolTypeManager::GetShortcut(protocol));
			model->Deserialize(data);
			shortcuts.push_back(model);
		}
	}
};

#endif