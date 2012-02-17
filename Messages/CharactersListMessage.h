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

	uint16 GetOpcode() const
	{ return SMSG_CHARACTERS_LIST; }

	CharactersListMessage()
	{
	}

	CharactersListMessage(bool hasStartupActions, std::vector<CharacterBaseInformationsPtr>& characters) : hasStartupActions(hasStartupActions), characters(characters)
	{
	}

	void Serialize(ByteBuffer& data) const
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
		characters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			CharacterBaseInformationsPtr model(Desperion::ProtocolTypeManager::GetCharacterBaseInformations(protocol));
			model->Deserialize(data);
			characters.push_back(model);
		}
	}
};

#endif