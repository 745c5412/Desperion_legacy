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

#ifndef __CHARACTERS_LIST_MESSAGE__
#define __CHARACTERS_LIST_MESSAGE__

class CharactersListMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_CHARACTERS_LIST; }

	CharactersListMessage(bool hasStartupActions, std::list<CharacterMinimals*>& characters)
	{
		m_buffer<<hasStartupActions;
		uint16 size = characters.size();
		m_buffer<<size;

		for(std::list<CharacterMinimals*>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			m_buffer<<uint16(CHARACTER_BASE_INFORMATIONS); // todo: Hardcore, recolor, etc
			m_buffer<<CharacterBaseInformations((*it)->id, (*it)->level, (*it)->name, (*it)->look, (*it)->breed,
				(*it)->sex);
		}
	}
};

#endif