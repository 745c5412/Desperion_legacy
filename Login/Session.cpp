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

template <> Session::HandlerStorageMap AbstractSession<LoginPacketHandler>::m_handlers;

bool IsIpBanned(std::string address)
{
	ResultPtr QR = Desperion::sDatabase->Query("SELECT banTime, banDate FROM ip_bans WHERE IP='%s' LIMIT 1;", address.c_str());
	if(!QR)
		return false;
	Field* fields = QR->Fetch();
	time_t banTime = fields[0].GetUInt64();
	time_t banDate = fields[1].GetUInt64();
	

	if(banDate + banTime < time(NULL))
	{
		Desperion::sDatabase->Execute("DELETE FROM ip_bans WHERE IP='%s' LIMIT 1;", address.c_str());
		return false;
	}
	else
		return true;
}

bool IsAccountBanned(uint32 guid)
{
	ResultPtr QR = Desperion::sDatabase->Query("SELECT banTime, banDate FROM account_bans WHERE guid=%u LIMIT 1;", guid);
	if(!QR)
		return false;
	Field* fields = QR->Fetch();
	time_t banTime = fields[0].GetUInt64();
	time_t banDate = fields[0].GetUInt64();
	

	if(banDate + banTime < time(NULL))
	{
		Desperion::sDatabase->Execute("DELETE FROM account_bans WHERE guid=%u LIMIT 1;", guid);
		return false;
	}
	else
		return true;
}

void Session::HandleAcquaintanceSearchMessage(ByteBuffer& packet)
{
	AcquaintanceSearchMessage data;
	data.Deserialize(packet);

	const char* query = "SELECT serverID FROM character_counts INNER JOIN accounts ON accounts.guid = character_counts.accountGuid "\
		"WHERE LOWER(accounts.pseudo)=LOWER('%s');";
	ResultPtr QR = Desperion::sDatabase->Query(query, Desperion::sDatabase->EscapeString(data.nickName).c_str());
	if(!QR)
	{
		Send(AcquaintanceSearchErrorMessage(2));
		return;
	}

	std::vector<int16> results;
	do
	{
		Field* fields = QR->Fetch();
		int16 id = fields[0].GetInt16();
		results.push_back(id);
	}while(QR->NextRow());
	
	Send(AcquaintanceServerListMessage(results));
}

bool Session::HandleServerSelection(GameServer* G, bool quiet)
{
	if(G == NULL)
		return false;

	uint8 state = G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber());
	if(!CanSelect(state))
	{
		uint8 reason;
		switch(state)
		{
		case FULL:
			reason = SERVER_CONNECTION_ERROR_SUBSCRIBERS_ONLY;
			break;
		case STATUS_UNKNOWN:
			reason = SERVER_CONNECTION_ERROR_NO_REASON;
			break;
		default:
			reason = SERVER_CONNECTION_ERROR_DUE_TO_STATUS;
			break;
		}
		
		if(!quiet)
			Send(SelectedServerRefusedMessage(G->GetID(), reason, G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber())));
		return false;
	}
	//todo: restriction de communauté et de géolocalisation
	
	std::string ticket = GenerateRandomKey();
	if(!Desperion::sDatabase->Execute("UPDATE accounts SET ticket='%s' WHERE guid=%u LIMIT 1;", ticket.c_str(), m_data[FLAG_GUID].intValue))
	{
		if(!quiet)
			Send(SelectedServerRefusedMessage(G->GetID(), SERVER_CONNECTION_ERROR_NO_REASON, 
				G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber())));
		return false;
	}

	Send(SelectedServerDataMessage(G->GetID(), G->GetIP(), G->GetPort(), true, ticket));
	m_socket->close();
	return true;
}

void Session::HandleServerSelectionMessage(ByteBuffer& packet)
{
	ServerSelectionMessage data;
	data.Deserialize(packet);

	HandleServerSelection(World::Instance().GetGameServer(data.id), false);
}

GameServerInformations* Session::GetServerStatusMessage(const GameServer* G, uint8 count)
{
	uint8 state = G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber());
	return new GameServerInformations(G->GetID(), state, 0,
		CanSelect(state), count, 0);
}

void Session::SendServersList()
{
	struct Count
	{
		uint8 count;
		Count()
		{ count = 0; }
	};

	std::tr1::unordered_map<uint16, Count> counts;
	ResultPtr QR = Desperion::sDatabase->Query("SELECT serverID FROM character_counts WHERE accountGuid=%u;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		do
		{
			Field* fields = QR->Fetch();
			uint16 serverID = fields[0].GetUInt16();
			++counts[serverID].count;
		}while(QR->NextRow());
	}
	

	const World::GameServerMap& servers = World::Instance().GetGameServers();
	std::vector<GameServerInformationsPtr> infos;
	for(World::GameServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it)
		infos.push_back(GameServerInformationsPtr(GetServerStatusMessage(it->second, counts[it->first].count)));
	Send(ServersListMessage(infos));
}

void Session::HandleIdentification(IdentificationMessage* data)
{
	if(IsIpBanned(m_socket->remote_endpoint().address().to_string()))
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		throw ServerError("Wrong crendentials");
	}
	else if(!VerifyVersion(*(data->version)))
	{
		Send(IdentificationFailedMessage(BAD_VERSION));
		throw ServerError("Bad Version");
	}

	const char* query = "SELECT password, guid, question, pseudo, logged, level, lastServer, subscriptionEnd FROM accounts WHERE account='%s' LIMIT 1;";
	ResultPtr QR = Desperion::sDatabase->Query(query, data->userName.c_str());
	
	if(!QR)
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		throw ServerError("Wrong credentials");
	}

	Field* fields = QR->Fetch();
	std::string pass = data->password;
	const char* charPass = pass.c_str();
	md5_state_t state;
	md5_byte_t digest[16];
	char hex_output[16*2 + 1];
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)charPass, strlen(charPass));
	md5_finish(&state, digest);
	for (int i = 0; i < 16; i++)
		sprintf(hex_output + i * 2, "%02x", digest[i]);

	if(std::string(fields[0].GetString()) != std::string(hex_output))
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		throw ServerError("Wrong crendentials");
	}
	
	uint32 guid = fields[1].GetUInt32();
	if(IsAccountBanned(guid))
	{
		Send(IdentificationFailedMessage(BANNED));
		throw ServerError("Banned");
	}

	Session* S = World::Instance().GetSession(guid);
	bool alreadyConnected = false;
	if(S != NULL)
	{
		alreadyConnected = true;
		S->GetSocket()->close();
	}

	m_subscriptionEnd = fields[7].GetUInt64();
	m_data[FLAG_LAST_SERVER].intValue = fields[6].GetUInt16();
	m_data[FLAG_PSEUDO].stringValue = fields[3].GetString();
	m_data[FLAG_GUID].intValue = guid;
	m_data[FLAG_LEVEL].intValue = fields[5].GetUInt8();
	m_data[FLAG_QUESTION].stringValue = fields[2].GetString();
	m_data[FLAG_ACCOUNT].stringValue = data->userName;
	

	World::Instance().AddSession(this);

	Send(IdentificationSuccessMessage(m_data[FLAG_LEVEL].intValue > 0, alreadyConnected, m_data[FLAG_PSEUDO].stringValue,
		m_data[FLAG_GUID].intValue, 0, m_data[FLAG_QUESTION].stringValue, m_subscriptionEnd));
}

void Session::HandleIdentificationWithServerIdMessage(ByteBuffer& packet)
{
	IdentificationWithServerIdMessage data;
	data.Deserialize(packet);
	HandleIdentification(&data);

	if(!HandleServerSelection(World::Instance().GetGameServer(data.serverId), true))
			SendServersList();
}

void Session::HandleIdentificationMessage(ByteBuffer& packet)
{
	IdentificationMessage data;
	data.Deserialize(packet);
	HandleIdentification(&data);

	if(data.autoConnect)
	{
		if(HandleServerSelection(World::Instance().GetGameServer(m_data[FLAG_LAST_SERVER].intValue), true))
			return;
	}
	SendServersList();
}

void Session::InitHandlersTable()
{
	m_handlers[CMSG_IDENTIFICATION].Handler = &Session::HandleIdentificationMessage;
	m_handlers[CMSG_IDENTIFICATION].Flag = FLAG_NOT_CONNECTED;

	// TODO: file d'attente

	m_handlers[CMSG_SERVER_SELECTION].Handler = &Session::HandleServerSelectionMessage;
	m_handlers[CMSG_SERVER_SELECTION].Flag = FLAG_OUT_OF_QUEUE;

	m_handlers[CMSG_ACQUAINTANCE_SEARCH].Handler = &Session::HandleAcquaintanceSearchMessage;
	m_handlers[CMSG_ACQUAINTANCE_SEARCH].Flag = FLAG_OUT_OF_QUEUE;

	m_handlers[CMSG_IDENTIFICATION_WITH_SERVER_ID].Handler = &Session::HandleIdentificationWithServerIdMessage;
	m_handlers[CMSG_IDENTIFICATION_WITH_SERVER_ID].Flag = FLAG_NOT_CONNECTED;
}

Session::~Session()
{
	if(m_data[FLAG_GUID].intValue != 0)
	{
		World::Instance().DeleteSession(m_data[FLAG_GUID].intValue);
		Log::Instance().outDebug("Client %u disconnected", m_data[FLAG_GUID].intValue);
	}
}

void Session::Start()
{
	Send(ProtocolRequired(PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD));
	m_key = GenerateRandomKey();
	Send(HelloConnectMessage(2, m_key));

	Run();
}