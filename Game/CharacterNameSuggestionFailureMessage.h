/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __CHARACTER_NAME_SUGGESTION_FAILURE_MESSAGE__
#define __CHARACTER_NAME_SUGGESTION_FAILURE_MESSAGE__

enum NicknameGeneratingFailure
{
	NICKNAME_GENERATOR_RETRY_TOO_SHORT = 1,
	NICKNAME_GENERATOR_UNAVAILABLE = 2,
};

class CharacterNameSuggestionFailureMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_CHARACTER_NAME_SUGGESTION_FAILURE; }

	CharacterNameSuggestionFailureMessage(uint8 reason)
	{
		m_buffer<<reason;
	}
};

#endif