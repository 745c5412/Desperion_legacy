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

#ifndef __SELECTED_SERVER_REFUSED_MESSAGE__
#define __SELECTED_SERVER_REFUSED_MESSAGE__

class SelectedServerRefusedMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_SELECTED_SERVER_REFUSED; }

	SelectedServerRefusedMessage(int16 id, int8 reason, int8 state)
	{
		m_buffer<<id<<reason<<state;
	}
};

#endif