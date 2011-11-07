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

#ifndef __CHAT_ERROR_MESSAGE__
#define __CHAT_ERROR_MESSAGE__

enum ChatError
{
	CHAT_ERROR_UNKNOWN = 0,
	CHAT_ERROR_RECEIVER_NOT_FOUND = 1,
	CHAT_ERROR_INTERIOR_MONOLOGUE = 2,
	CHAT_ERROR_NO_GUILD = 3,
	CHAT_ERROR_NO_PARTY = 4,
	CHAT_ERROR_ALIGN = 5,
	CHAT_ERROR_INVALID_MAP = 6,
	CHAT_ERROR_NO_PARTY_ARENA = 7,
};

class ChatErrorMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CHAT_ERROR; }

	ChatErrorMessage(int8 reason)
	{
		m_buffer<<reason;
	}
};

#endif