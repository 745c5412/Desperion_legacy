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

#include "StdAfx.h"

template<> Session::HandlerStorageMap BaseSession<GamePacketHandler>::m_handlers;

void Session::InitHandlersTable()
{
	m_handlers[CMSG_AUTHENTICATION_TICKET].Handler = &Session::HandleAuthenticationTicketMessage;
	m_handlers[CMSG_AUTHENTICATION_TICKET].Flag = FLAG_NOT_CONNECTED;
	m_handlers[CMSG_ADMIN_COMMAND].Handler = &Session::HandleAdminCommandMessage;
	m_handlers[CMSG_ADMIN_QUIET_COMMAND].Handler = &Session::HandleAdminQuietCommandMessage;

	m_handlers[CMSG_CHARACTERS_LIST_REQUEST].Handler = &Session::HandleCharactersListRequestMessage;
	m_handlers[CMSG_CHARACTERS_LIST_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_DELETION_REQUEST].Handler = &Session::HandleCharacterDeletionRequestMessage;
	m_handlers[CMSG_CHARACTER_DELETION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_NAME_SUGGESTION_REQUEST].Handler = &Session::HandleCharacterNameSuggestionRequestMessage;
	m_handlers[CMSG_CHARACTER_NAME_SUGGESTION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_SELECTION].Handler = &Session::HandleCharacterSelectionMessage;
	m_handlers[CMSG_CHARACTER_SELECTION].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_CREATION_REQUEST].Handler = &Session::HandleCharacterCreationRequestMessage;
	m_handlers[CMSG_CHARACTER_CREATION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;

	m_handlers[CMSG_GAME_CONTEXT_CREATE_REQUEST].Handler = &Session::HandleGameContextCreateRequestMessage;
	m_handlers[CMSG_MAP_INFORMATIONS_REQUEST].Handler = &Session::HandleMapInformationsRequestMessage;
	m_handlers[CMSG_GAME_MAP_MOVEMENT_REQUEST].Handler = &Session::HandleGameMapMovementRequestMessage;
	m_handlers[CMSG_GAME_MAP_MOVEMENT_CONFIRM].Handler = &Session::HandleGameMapMovementConfirmMessage;
	m_handlers[CMSG_CHANGE_MAP].Handler = &Session::HandleChangeMapMessage;
}

void Session::HandleAdminCommandMessage(ByteBuffer& packet)
{
	if(m_data[FLAG_LEVEL].intValue < 1)
		return;
	AdminCommandMessage data(packet);
}

void Session::HandleAdminQuietCommandMessage(ByteBuffer& packet)
{
	if(m_data[FLAG_LEVEL].intValue < 1)
		return;
	AdminQuietCommandMessage data(packet);
	// todo: faire un vrai système de commande comme pour desperion 1

	std::vector<std::string> table;
	Desperion::Split(table, data.content, ' ');
	int mapId = atoi(table.at(1).c_str());
	
	Map* newMap = World::Instance().GetMap(mapId);
	if(newMap == NULL)
		return;

	m_char->SetCell(399);
	m_char->GetMap()->RemoveActor(m_char->GetGuid());
	newMap->AddActor(m_char);
	m_char->SetMap(newMap);
	Send(CurrentMapMessage(m_char->GetMap()->GetId()));
}

void Session::SendToMap(const DofusMessage& data, bool self)
{
	std::list<DisplayableEntity*>& actors = m_char->GetMap()->GetActors();
	for(std::list<DisplayableEntity*>::iterator it = actors.begin(); it != actors.end(); ++it)
	{
		if(!(*it)->IsCharacter())
			continue;
		Character* ch = ToCharacter(*it);
		if(ch->GetGuid() == m_char->GetGuid() && !self)
			continue;
		ch->GetSession()->Send(data);
	}
}

void Session::HandleAuthenticationTicketMessage(ByteBuffer& packet)
{
	AuthenticationTicketMessage data(packet);

	const char* query = "SELECT guid, answer, pseudo, level, lastIP, lastConnectionDate, subscriptionEnd FROM accounts WHERE ticket='%s' LIMIT 1;";
	QueryResult* QR = Desperion::eDatabase->Query(query, data.ticket.c_str());
	if(QR)
	{
		Field* fields = QR->Fetch();
		m_data[FLAG_GUID].intValue = fields[0].GetUInt32();
		m_data[FLAG_PSEUDO].stringValue = fields[2].GetString();
		m_data[FLAG_LEVEL].intValue = fields[3].GetUInt8();
		m_data[FLAG_ANSWER].stringValue = fields[1].GetString();
		m_data[FLAG_LAST_CONN].intValue = fields[4].GetUInt32();
		m_data[FLAG_LAST_IP].stringValue = fields[5].GetString();
		m_subscriptionEnd = fields[6].GetUInt32();
	}
	else
	{
		Send(AuthenticationTicketRefusedMessage());
		throw ServerError("Failed ticket authentification!");
	}
	delete QR;

	QR = Desperion::eDatabase->Query("SELECT channels, disallowed FROM account_channels WHERE guid=%u LIMIT 1;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		Field* fields = QR->Fetch();
		std::string channels = fields[0].GetString();
		std::string disallowed = fields[1].GetString();

		if(!channels.empty())
		{
			std::vector<std::string> table;
			Desperion::Split(table, channels, ',');
			for(uint8 a = 0; a < table.size(); ++a)
			{
				uint32 chan = atoi(table.at(a).c_str());
				m_channels.push_back(chan);
			}
		}
		if(!disallowed.empty())
		{
			std::vector<std::string> table;
			Desperion::Split(table, disallowed, ',');
			for(uint8 a = 0; a < table.size(); ++a)
			{
				uint32 dis = atoi(table.at(a).c_str());
				m_disallowed.push_back(dis);
			}
		}
	}
	else
		Desperion::eDatabase->Execute("INSERT INTO account_channels VALUES(%u, '', '');", m_data[FLAG_GUID].intValue);
	delete QR;

	QR = Desperion::eDatabase->Query("SELECT friends, ennemies FROM account_social WHERE guid=%u LIMIT 1;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		Field* fields = QR->Fetch();
		std::string friends = fields[0].GetString();
		std::string ennemies = fields[1].GetString();

		if(friends != "")
		{
			std::vector<std::string> table;
			Desperion::Split(table, friends, ',');
			for(uint8 a = 0; a < table.size(); a++)
			{
				uint32 account = atoi(table.at(a).c_str());
				m_friends.push_back(account);
			}
		}
		if(ennemies != "")
		{
			std::vector<std::string> table;
			Desperion::Split(table, ennemies, ',');
			for(uint8 a = 0; a < table.size(); a++)
			{
				uint32 account = atoi(table.at(a).c_str());
				m_ennemies.push_back(account);
			}
		}
	}
	else
		Desperion::eDatabase->Execute("INSERT INTO account_social VALUES(%u, '', '');", m_data[FLAG_GUID].intValue);
	delete QR;

	uint16 servID = Desperion::Config::Instance().GetUInt(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT);
	Desperion::eDatabase->Execute("UPDATE accounts SET ticket='', logged=%u WHERE guid=%u LIMIT 1;", servID, 
		m_data[FLAG_GUID].intValue);

	World::Instance().AddSession(this);

	Send(AuthenticationTicketAcceptedMessage());
	Send(AccountCapabilitiesMessage(m_data[FLAG_GUID].intValue, false, 0x1fff, 0x1fff));
	std::vector<int16> features;
	features.push_back(1); // ankabox
	features.push_back(2); // kolizéum
	Send(ServerOptionalFeaturesMessage(features));
}

Session::~Session()
{
	if(m_char != NULL)
	{
		m_char->GetMap()->RemoveActor(m_char->GetGuid());
		delete m_char;
	}
	if(m_data[FLAG_GUID].intValue != 0)
	{
		World::Instance().DeleteSession(m_data[FLAG_GUID].intValue);
		Log::Instance().outDebug("Client %u disconnected", m_data[FLAG_GUID].intValue);
	}
}

void Session::Start()
{
	Send(HelloGame());

	Run();
}