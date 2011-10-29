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
	
	m_handlers[CMSG_CHAT_CLIENT_MULTI].Handler = &Session::HandleChatClientMultiMessage;
	m_handlers[CMSG_CHAT_CLIENT_MULTI_WITH_OBJECT].Handler = &Session::HandleChatClientMultiWithObjectMessage;
	m_handlers[CMSG_CHAT_CLIENT_PRIVATE].Handler = &Session::HandleChatClientPrivateMessage;
	m_handlers[CMSG_CHAT_CLIENT_PRIVATE_WITH_OBJECT].Handler = &Session::HandleChatClientPrivateWithObjectMessage;

	m_handlers[CMSG_OBJECT_DROP].Handler = &Session::HandleObjectDropMessage;
	m_handlers[CMSG_OBJECT_DELETE].Handler = &Session::HandleObjectDeleteMessage;
	m_handlers[CMSG_OBJECT_SET_POSITION].Handler = &Session::HandleObjectSetPositionMessage;
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
		Desperion::FastSplit<','>(m_channels, std::string(fields[0].GetString()), Desperion::SplitInt, false);
		Desperion::FastSplit<','>(m_channels, std::string(fields[1].GetString()), Desperion::SplitInt, false);
	}
	else
		Desperion::eDatabase->Execute("INSERT INTO account_channels VALUES(%u, '', '');", m_data[FLAG_GUID].intValue);
	delete QR;

	QR = Desperion::eDatabase->Query("SELECT friends, ennemies FROM account_social WHERE guid=%u LIMIT 1;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		Field* fields = QR->Fetch();
		Desperion::FastSplit<','>(m_friends, std::string(fields[0].GetString()), Desperion::SplitInt, false);
		Desperion::FastSplit<','>(m_ennemies, std::string(fields[1].GetString()), Desperion::SplitInt, false);
	}
	else
		Desperion::eDatabase->Execute("INSERT INTO account_social VALUES(%u, '', '');", m_data[FLAG_GUID].intValue);
	delete QR;

	uint16 servID = Desperion::Config::Instance().GetUInt(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT);
	Desperion::eDatabase->Execute("UPDATE accounts SET ticket='', logged=%u, lastServer=%u WHERE guid=%u LIMIT 1;", servID, 
		servID, m_data[FLAG_GUID].intValue);

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
		m_char->Save();
		delete m_char;
	}
	if(m_data[FLAG_GUID].intValue != 0)
	{
		Desperion::eDatabase->Execute("UPDATE accounts SET logged=0 WHERE guid=%u LIMIT 1;", m_data[FLAG_GUID].intValue);
		World::Instance().DeleteSession(m_data[FLAG_GUID].intValue);
		Log::Instance().outDebug("Client %u disconnected", m_data[FLAG_GUID].intValue);
	}
}

void Session::Start()
{
	Send(HelloGame());

	Run();
}