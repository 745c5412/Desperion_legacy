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

#ifndef __CHARACTER_DELETION_ERROR_MESSAGE__
#define __CHARACTER_DELETION_ERROR_MESSAGE__

enum CharacterDeletionError
{
	DEL_ERR_NO_REASON = 1,
	DEL_ERR_TOO_MANY_CHAR_DELETION = 2,
	DEL_ERR_BAD_SECRET_ANSWER = 3,
	DEL_ERR_RESTRICED_ZONE = 4,
};

class CharacterDeletionErrorMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_CHARACTER_DELETION_ERROR; }

	CharacterDeletionErrorMessage(uint8 reason)
	{
		m_buffer<<reason;
	}
};

#endif