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

#ifndef __INVENTORY_CONTENT_MESSAGE__
#define __INVENTORY_CONTENT_MESSAGE__

class InventoryContentMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_INVENTORY_CONTENT; }

	InventoryContentMessage(const std::list<PlayerItem*>& items, int kamas)
	{
		uint16 size = items.size();
		m_buffer<<size;
		for(std::list<PlayerItem*>::const_iterator it = items.begin(); it != items.end(); ++it)
		{
			ObjectItem obj(*it);
			m_buffer<<obj;
		}
		m_buffer<<kamas;
	}
};

#endif