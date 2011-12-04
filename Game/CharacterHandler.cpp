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
	CharactersListRequestMessage data;
	data.Deserialize(packet);

	std::list<CharacterMinimals*> characters = World::Instance().GetCharactersByAccount(m_data[FLAG_GUID].intValue);
	Send(CharactersListMessage(false, characters));
}

void Session::HandleCharacterDeletionRequestMessage(ByteBuffer& packet)
{
	CharacterDeletionRequestMessage data;
	data.Deserialize(packet);

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
	if(!Desperion::sDatabase->Execute("DELETE FROM characters WHERE guid=%u LIMIT 1;", toDelete->id))
	{
		Send(CharacterDeletionErrorMessage(DEL_ERR_NO_REASON));
		return;
	}
	Desperion::sDatabase->Execute("DELETE FROM character_minimals WHERE id=%u LIMIT 1;", toDelete->id);
	Desperion::sDatabase->Execute("DELETE FROM character_stats WHERE guid=%u LIMIT 1;", toDelete->id);
	Desperion::eDatabase->Execute("DELETE FROM character_counts WHERE accountGuid=%u AND serverID=%u LIMIT 1;", m_data[FLAG_GUID].intValue,
		Desperion::Config::Instance().GetParam(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT));
	delete toDelete;

	Send(CharactersListMessage(false, characters));
}

void Session::HandleCharacterNameSuggestionRequestMessage(ByteBuffer& packet)
{
	CharacterNameSuggestionRequestMessage data;
	data.Deserialize(packet);

	uint32 time = getMSTime();
	if(time < m_lastNameSuggestionRequest + 
		Desperion::Config::Instance().GetParam(NAME_SUGGESTION_RETRY_TIME_STRING, NAME_SUGGESTION_RETRY_TIME_DEFAULT))
	{
		Send(CharacterNameSuggestionFailureMessage(NICKNAME_GENERATOR_RETRY_TOO_SHORT));
		return;
	}

	m_lastNameSuggestionRequest = time;
	
	struct RandomName
	{
	private:
		bool isComposedName;
		uint8 nameSize;
		std::vector<uint8> vowelIndexes;
		std::string str;
		std::string chars;
		std::string vowels;
		size_t charsSize;
		size_t vowelsSize;
		
		uint8 RandomSize()
		{
			if(!isComposedName)
				nameSize = RandomUInt(6, 10);
			else
				nameSize = RandomUInt(3, 7);
			return RandomUInt(1, ceil(double(nameSize) / 2));
		}
		
		bool IsVowel(uint8 index)
		{
			for(uint8 a = 0; a < vowelIndexes.size(); ++a)
				if(vowelIndexes[a] == index)
					return true;
			return false;
		}
		
		void FillVowelIndexes(uint8 count)
		{
			vowelIndexes.clear();
			while(vowelIndexes.size() != count)
			{
				uint8 index = RandomUInt(0, count - 1);
				if(IsVowel(index))
					continue;
				vowelIndexes.push_back(index);
			}
		}
		
		void RandomStr()
		{
			for(uint8 a = 0; a < nameSize; ++a)
			{
				char letter;
				if(IsVowel(a))
					letter = vowels[RandomUInt(vowelsSize)];
				else
					letter = chars[RandomUInt(charsSize)];
				if(a == 0)
					letter = std::toupper(letter);
				str += letter;
			}
		}
		
	public:
		std::string GetStr() const
		{ return str; }
	
		RandomName()
		{
			chars = "bcdfghjklmnpqrstvwxz";
			vowels = "aeiouy";
			str = "";
			charsSize = chars.size() - 1;
			vowelsSize = vowels.size() - 1;
			isComposedName = RandomDouble() < 0.5;
			FillVowelIndexes(RandomSize());
			RandomStr();
			if(isComposedName)
			{
				str += '-';
				FillVowelIndexes(RandomSize());
				RandomStr();
			}
		}
	};
	
	RandomName name;
	Send(CharacterNameSuggestionSuccessMessage(name.GetStr()));
}

void Session::HandleCharacterSelectionMessage(ByteBuffer& packet)
{
	CharacterSelectionMessage data;
	data.Deserialize(packet);

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

	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM characters JOIN character_stats ON characters.guid=character_stats.guid \
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
		
	}catch(const ServerError& err)
	{ 
		delete m_char;
		
		m_char = NULL;
		Log::Instance().outError(err.what());
		Send(CharacterSelectedErrorMessage());
		return;
	}

	SendCharacterSelectedSuccess(toSelect);
}

void Session::SendCharacterSelectedSuccess(CharacterMinimals* ch)
{
	Send(CharacterSelectedSuccessMessage(ch));
	m_char->GetMap()->AddActor(m_char);
	
	Send(InventoryContentMessage(m_char->GetItems(), m_char->GetStats().GetKamas()));
	Send(InventoryWeightMessage(m_char->GetCurrentPods(), m_char->GetMaxPods()));
	std::tr1::unordered_map<int16, std::vector<int16> > sets = m_char->GetTotalItemSets();
	for(std::tr1::unordered_map<int16, std::vector<int16> >::iterator it = sets.begin(); it != sets.end(); ++it)
	{
		ItemSet* set = World::Instance().GetItemSet(it->first);
		const std::vector<EffectInstance*>& effects = set->GetEffect(it->second.size());
		ItemSet::ApplyEffects(m_char, effects, true);
		Send(SetUpdateMessage(set->GetId(), it->second, effects));
	}
	Send(EnabledChannelsMessage(m_channels, m_disallowed));
	Send(CharacterStatsListMessage(m_char));
}

void Session::HandleCharacterCreationRequestMessage(ByteBuffer& packet)
{
	CharacterCreationRequestMessage data;
	data.Deserialize(packet);

	if(World::Instance().GetCharacterMinimals(data.name) != NULL)
	{
		Send(CharacterCreationResultMessage(ERR_NAME_ALREADY_EXISTS));
		return;
	}
	else if(!DofusUtils::CheckName(data.name))
	{
		Send(CharacterCreationResultMessage(ERR_INVALID_NAME));
		return;
	}

	int16 id = Desperion::Config::Instance().GetParam(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT);
	ResultPtr QR = Desperion::eDatabase->Query("SELECT * FROM character_counts WHERE accountGuid=%u;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		if(QR->GetRowCount() > Desperion::Config::Instance().GetParam(MAX_CHARACTERS_COUNT_STRING, MAX_CHARACTERS_COUNT_DEFAULT))
		{
			Send(CharacterCreationResultMessage(ERR_TOO_MANY_CHARACTERS));
			return;
		}
	}
	

	int startMap = Desperion::Config::Instance().GetParam(CUSTOM_START_MAP_STRING, CUSTOM_START_MAP_DEFAULT);
	int16 startCell = Desperion::Config::Instance().GetParam(CUSTOM_START_CELL_STRING, CUSTOM_START_CELL_DEFAULT);
	Map* map = World::Instance().GetMap(startMap);
	if(map == NULL || map->GetCell(startCell).id == -1)
	{
		Send(CharacterCreationResultMessage(ERR_NO_REASON));
		return;
	}

	int guid = World::Instance().GetNextCharacterGuid();
	if(!Desperion::sDatabase->Execute("INSERT INTO characters VALUES(%u, '%s', %u, %u, '%s', %u, %u, '', 0, -1, 0, 0, 0, '%s');",
		guid, Desperion::Config::Instance().GetParam<std::string>(START_ZAAPS_STRING, START_ZAAPS_DEFAULT).c_str(),
		startMap, startCell, "", startMap, startCell,
		Desperion::Config::Instance().GetParam<std::string>(START_EMOTES_STRING, START_EMOTES_DEFAULT).c_str()))
	{
		Send(CharacterCreationResultMessage(ERR_NO_REASON));
		return;
	}

	DEntityLook look;
	look.bonesId = 1;
	look.skins.push_back(data.breed * 10 + (data.sex ? 1 : 0));
	look.scales.push_back(140);
	// TODO: couleurs par defaut & indexage des couleurs
	look.indexedColors.push_back(data.colors[0]);
	look.indexedColors.push_back(data.colors[1]);
	look.indexedColors.push_back(data.colors[2]);
	look.indexedColors.push_back(data.colors[3]);
	look.indexedColors.push_back(data.colors[4]);
	uint8 level = Desperion::Config::Instance().GetParam(START_LEVEL_STRING, START_LEVEL_DEFAULT);
	bool full = Desperion::Config::Instance().GetParam(FULL_SCROLLED_STRING, FULL_SCROLLED_DEFAULT);
	Desperion::sDatabase->Execute("INSERT INTO character_minimals VALUES(%u, %u, '%s', '%s', %u, %u, %u);",
		guid, level, data.name.c_str(), look.ToString().c_str(), data.breed, data.sex, m_data[FLAG_GUID].intValue);
	Desperion::sDatabase->Execute("INSERT INTO character_stats VALUES(%u, %u, %u, %u, 0, 0, 0, 0, 0, 0, 10000, %u, %u, %u, %u, %u, %u, \
								  %llu, 0);",
								  guid, Desperion::Config::Instance().GetParam(START_KAMAS_STRING, START_KAMAS_DEFAULT), (level - 1) * 5,
								  level - 1, full ? 101 : 0, full ? 101 : 0, full ? 101 : 0, full ? 101 : 0, full ? 101 : 0, 
								  full ? 101 : 0, 0); // dernier 0: xp --> TODO
	Desperion::eDatabase->Execute("INSERT INTO character_counts VALUES(%u, %u);", m_data[FLAG_GUID].intValue, id);

	CharacterMinimals* ch = new CharacterMinimals;
	ch->id = guid;
	ch->account = m_data[FLAG_GUID].intValue;
	ch->breed = data.breed;
	ch->level = level;
	ch->look = look;
	ch->name = data.name;
	ch->onlineCharacter = NULL;
	ch->sex = data.sex;
	World::Instance().AddCharacterMinimals(ch);

	Send(CharacterCreationResultMessage(OK));

	QR = Desperion::sDatabase->Query("SELECT * FROM characters JOIN character_stats ON characters.guid=character_stats.guid \
									   JOIN character_breeds ON character_breeds.id=%u WHERE \
									   characters.guid=%u LIMIT 1;", ch->breed, ch->id);
	if(!QR)
	{
		Log::Instance().outError("Character creation guid %u went wrong...", ch->id);
		return;
	}
	Field* fields = QR->Fetch();
	m_char = new Character;
	m_char->Init(fields, ch, this);
	SendCharacterSelectedSuccess(ch);
}