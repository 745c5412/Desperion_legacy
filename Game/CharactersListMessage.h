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
	bool hasStartupActions;
	std::vector<CharacterBaseInformationsPtr> characters;

	virtual uint16 GetOpcode() const
	{ return SMSG_CHARACTERS_LIST; }

	CharactersListMessage()
	{
	}

	CharactersListMessage(bool hasStartupActions, std::list<CharacterMinimals*>& characters) : hasStartupActions(hasStartupActions)
	{
		for(std::list<CharacterMinimals*>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			// TODO: recolorInformations, etc
			this->characters.push_back(CharacterBaseInformationsPtr(new CharacterBaseInformations((*it)->id,
				(*it)->level, (*it)->name, EntityLookPtr((*it)->GetLook()), (*it)->breed, (*it)->sex)));
		}
	}

	void Serialize(ByteBuffer& data)
	{
		data<<hasStartupActions;
		uint16 size = characters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<characters[a]->GetProtocol();
			characters[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>hasStartupActions;
		uint16 size;
		characters.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			CharacterBaseInformationsPtr ch(new CharacterBaseInformations);
			ch->Deserialize(data);
			characters.push_back(ch);
		}
	}
};

#endif