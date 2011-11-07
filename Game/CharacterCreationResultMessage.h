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

#ifndef __CHARACTER_CREATION_RESULT_MESSAGE__
#define __CHARACTER_CREATION_RESULT_MESSAGE__

enum CharacterCreationResult
{
	OK = 0,
	ERR_NO_REASON = 1,
	ERR_INVALID_NAME = 2,
	ERR_NAME_ALREADY_EXISTS = 3,
	ERR_TOO_MANY_CHARACTERS = 4,
	ERR_NOT_ALLOWED = 5,
	ERR_NEW_PLAYER_NOT_ALLOWED = 6,
	ERR_RESTRICED_ZONE = 7,
};

class CharacterCreationResultMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CHARACTER_CREATION_RESULT; }

	CharacterCreationResultMessage(int8 reason)
	{
		m_buffer<<reason;
	}
};

#endif