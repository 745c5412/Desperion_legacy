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

#ifndef __CHARACTERS_LIST_WITH_MODIFICATIONS_MESSAGE__
#define __CHARACTERS_LIST_WITH_MODIFICATIONS_MESSAGE__

class CharactersListWithModificationsMessage : public CharactersListMessage
{
public:
	std::vector<CharacterToRecolorInformationPtr> charactersToRecolor;
	std::vector<int> charactersToRename;
	std::vector<int> unusableCharacters;

	uint16 GetOpcode() const
	{ return SMSG_CHARACTERS_LIST_WITH_MODIFICATIONS; }

	CharactersListWithModificationsMessage()
	{
	}

	CharactersListWithModificationsMessage(bool hasStartupActions, std::vector<CharacterBaseInformationsPtr>& characters, std::vector<CharacterToRecolorInformationPtr>& charactersToRecolor, std::vector<int>& charactersToRename, std::vector<int>& unusableCharacters) : CharactersListMessage(hasStartupActions, characters), charactersToRecolor(charactersToRecolor), charactersToRename(charactersToRename), unusableCharacters(unusableCharacters)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharactersListMessage::Serialize(data);
		uint16 size = charactersToRecolor.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<charactersToRecolor[a]->GetProtocol();
			charactersToRecolor[a]->Serialize(data);
		}
		uint16 size = charactersToRename.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<charactersToRename[a];
		uint16 size = unusableCharacters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<unusableCharacters[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		CharactersListMessage::Deserialize(data);
		charactersToRecolor.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			CharacterToRecolorInformationPtr model(Desperion::ProtocolTypeManager::GetCharacterToRecolorInformation(protocol));
			model->Deserialize(data);
			charactersToRecolor.push_back(model);
		}
		charactersToRename.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			charactersToRename.push_back(val);
		}
		unusableCharacters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			unusableCharacters.push_back(val);
		}
	}
};

#endif