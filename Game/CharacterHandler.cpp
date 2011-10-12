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

#include "StdAfx.h"

void Session::HandleCharactersListRequestMessage(ByteBuffer& packet)
{
	CharactersListRequestMessage data(packet);

	std::list<CharacterMinimals*> characters = World::Instance().GetCharactersByAccount(m_data[FLAG_GUID].intValue);
	Send(CharactersListMessage(false, characters));
}

void Session::HandleCharacterDeletionRequestMessage(ByteBuffer& packet)
{
	CharacterDeletionRequestMessage data(packet);

	CharacterMinimals* toDelete = NULL;
	std::list<CharacterMinimals*> characters = World::Instance().GetCharactersByAccount(m_data[FLAG_GUID].intValue);
	for(std::list<CharacterMinimals*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if((*it)->id == data.characterId)
		{
			toDelete = *it;
			characters.erase(it);
			break;
		}
	}
	if(toDelete == NULL)
	{
		Send(CharacterDeletionErrorMessage(DEL_ERR_NO_REASON));
		return;
	}

	if(toDelete->level > 20)
	{
		std::ostringstream stream;
		stream<<toDelete->id<<"~"<<m_data[FLAG_ANSWER].stringValue;
		std::string result = stream.str();
		const char* charResult = result.c_str();
		md5_state_t state;
		md5_byte_t digest[16];
		char hex_output[16*2 + 1];
		md5_init(&state);
		md5_append(&state, (const md5_byte_t *)charResult, strlen(charResult));
		md5_finish(&state, digest);
		for (int i = 0; i < 16; i++)
			sprintf(hex_output + i * 2, "%02x", digest[i]);
		if(std::string(hex_output) != data.secretAnswerHash)
		{
			Send(CharacterDeletionErrorMessage(DEL_ERR_BAD_SECRET_ANSWER));
			return;
		}
	}

	World::Instance().DeleteCharacterMinimals(toDelete->id);
	Desperion::sDatabase->Execute("DELETE FROM character_minimals JOIN characters ON character_minimals.id = characters.guid WHERE characters.guid=%u LIMIT 1;", toDelete->id);
	delete toDelete;

	Send(CharactersListMessage(false, characters));
}

void Session::HandleCharacterNameSuggestionRequestMessage(ByteBuffer& packet)
{
	CharacterNameSuggestionRequestMessage data(packet);

	uint32 time = getMSTime();
	if(time < m_lastNameSuggestionRequest + 
		Desperion::Config::Instance().GetUInt(NAME_SUGGESTION_RETRY_TIME_STRING, NAME_SUGGESTION_RETRY_TIME_DEFAULT))
	{
		Send(CharacterNameSuggestionFailureMessage(NICKNAME_GENERATOR_RETRY_TOO_SHORT));
		return;
	}

	m_lastNameSuggestionRequest = time;

	std::string name = "";
	std::string chars = "bcdfghjklmnpqrstvwxz";
	std::string vowels = "aeiouy";
	size_t charsSize = chars.size() - 1;
	size_t vowelsSize = vowels.size() - 1;

	uint32 B = RandomUInt(4) + 6;
	uint32 vorc = (int)floor(RandomDouble(1));
	for(uint32 a = 0; a < B; ++a)
	{
		char letter;
		if(a%2 ==  vorc)
		{
			int i = RandomUInt(vowelsSize);
			letter = vowels[i];
		}
		else
		{
			int i = RandomUInt(charsSize);
			letter = chars[i];
		}
		if(a == 0)
			letter = std::toupper(letter);
		name += letter;
	}

	Send(CharacterNameSuggestionSuccessMessage(name));
}

void Session::HandleCharacterSelectionMessage(ByteBuffer& packet)
{
	CharacterSelectionMessage data(packet);

	CharacterMinimals* toSelect = NULL;
	std::list<CharacterMinimals*> characters = World::Instance().GetCharactersByAccount(m_data[FLAG_GUID].intValue);
	for(std::list<CharacterMinimals*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if((*it)->id == data.id)
		{
			toSelect = *it;
			break;
		}
	}

	if(toSelect == NULL)
	{
		Send(CharacterSelectedErrorMessage());
		return;
	}

	QueryResult* QR = Desperion::sDatabase->Query("SELECT * FROM characters JOIN character_stats ON characters.guid=character_stats.guid \
									   JOIN character_breeds ON character_breeds.id=%u WHERE \
									   characters.guid=%u LIMIT 1;", toSelect->breed, toSelect->id);
	if(!QR)
	{
		Log::Instance().outError("Character ID %u hasn't got stats or breed! :O", toSelect->id);
		Send(CharacterSelectedErrorMessage());
		return;
	}
	Field* fields = QR->Fetch();
	m_char = new Character;

	try{
		m_char->Init(fields, toSelect, this);
		delete QR;
	}catch(const ServerError&)
	{ 
		delete m_char;
		delete QR;
		m_char = NULL;
		throw; 
	}

	Send(CharacterSelectedSuccessMessage(toSelect));
	m_char->GetMap()->AddActor(m_char);
}

void Session::HandleCharacterCreationRequestMessage(ByteBuffer& packet)
{
	CharacterCreationRequestMessage data(packet);

	int guid = World::Instance().GetNextCharacterGuid();
}