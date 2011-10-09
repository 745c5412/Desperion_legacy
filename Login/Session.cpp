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

#define PROTOCOL_BUILD 1412
#define PROTOCOL_REQUIRED_BUILD 1412

template <> Session::HandlerStorageMap BaseSession<LoginPacketHandler>::m_handlers;

bool IsIpBanned(std::string address)
{
	QueryResult* QR = Desperion::sDatabase->Query("SELECT banTime, banDate FROM ip_bans WHERE IP='%s' LIMIT 1;", address.c_str());
	if(!QR)
		return false;
	Field* fields = QR->Fetch();
	time_t banTime = fields[0].GetUInt64();
	time_t banDate = fields[0].GetUInt64();
	delete QR;

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
	QueryResult* QR = Desperion::sDatabase->Query("SELECT banTime, banDate FROM account_bans WHERE guid=%u LIMIT 1;", guid);
	if(!QR)
		return false;
	Field* fields = QR->Fetch();
	time_t banTime = fields[0].GetUInt64();
	time_t banDate = fields[0].GetUInt64();
	delete QR;

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
	AcquaintanceSearchMessage data(packet);

	const char* query = "SELECT serverID FROM character_counts INNER JOIN accounts ON accounts.guid = character_counts.accountGuid "\
		"WHERE LOWER(accounts.pseudo)=LOWER('%s');";
	QueryResult* QR = Desperion::sDatabase->Query(query, Desperion::sDatabase->EscapeString(data.nickName).c_str());
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
	delete QR;
	Send(AcquaintanceServerListMessage(results));
}

void Session::HandleServerSelectionMessage(ByteBuffer& packet)
{
	ServerSelectionMessage data(packet);

	GameServer* G = World::Instance().GetGameServer(data.id);
	if(G == NULL)
		return;

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
		
		Send(SelectedServerRefusedMessage(G->GetID(), reason, G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber())));
		return;
	}
	//todo: restriction de communauté et de géolocalisation
	
	std::string ticket = GenerateRandomKey();
	if(!Desperion::sDatabase->Execute("UPDATE accounts SET ticket='%s' WHERE guid=%u LIMIT 1;", ticket.c_str(), m_data[FLAG_GUID].intValue))
	{
		Send(SelectedServerRefusedMessage(G->GetID(), SERVER_CONNECTION_ERROR_NO_REASON, 
			G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber())));
		return;
	}

	Send(SelectedServerDataMessage(G->GetID(), G->GetIP(), G->GetPort(), true, ticket));
	m_socket->close();
}

GameServerInformations Session::GetServerStatusMessage(const GameServer* G, uint8 count)
{
	uint8 state = G->GetState(m_data[FLAG_LEVEL].intValue, IsSubscriber());
	return GameServerInformations(G->GetID(), state, 0,
		CanSelect(state), count, uint64(0));
}

void Session::HandleIdentificationMessage(ByteBuffer& packet)
{
	if(IsIpBanned(m_socket->remote_endpoint().address().to_string()))
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		throw ServerError("Wrong crendentials");
	}

	IdentificationMessage data(packet);
	if(!VerifyVersion(data.version))
	{
		Send(IdentificationFailedMessage(BAD_VERSION));
		throw ServerError("Bad Version");
	}

	const char* query = "SELECT password, guid, question, pseudo, logged, level, lastServer, subscriptionEnd FROM accounts WHERE account='%s' LIMIT 1;";
	QueryResult* QR = Desperion::sDatabase->Query(query, data.userName.c_str());
	
	if(!QR)
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		throw ServerError("Wrong credentials");
	}

	Field* fields = QR->Fetch();
	std::string dbPass = std::string(fields[0].GetString()) + m_key;
	const char* charDbPass = dbPass.c_str();
	md5_state_t state;
	md5_byte_t digest[16];
	char hex_output[16*2 + 1];
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)charDbPass, strlen(charDbPass));
	md5_finish(&state, digest);
	for (int i = 0; i < 16; i++)
		sprintf(hex_output + i * 2, "%02x", digest[i]);

	if(data.password != std::string(hex_output))
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

	uint16 lastServer = fields[6].GetUInt16();
	m_subscriptionEnd = fields[7].GetUInt32();
	m_data[FLAG_PSEUDO].stringValue = fields[3].GetString();
	m_data[FLAG_GUID].intValue = guid;
	m_data[FLAG_LEVEL].intValue = fields[5].GetUInt8();
	m_data[FLAG_QUESTION].stringValue = fields[2].GetString();
	m_data[FLAG_ACCOUNT].stringValue = data.userName;
	delete QR;

	Send(IdentificationSuccessMessage(m_data[FLAG_LEVEL].intValue, alreadyConnected, m_data[FLAG_PSEUDO].stringValue,
		m_data[FLAG_GUID].intValue, m_data[FLAG_QUESTION].stringValue, m_subscriptionEnd));

	struct Count
	{
		uint8 m_count;
		Count()
		{ m_count = 0; }
	};

	std::tr1::unordered_map<uint16, Count> counts;
	QR = Desperion::sDatabase->Query("SELECT serverID, count FROM character_counts WHERE accountGuid=%u;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		do
		{
			Field* fields = QR->Fetch();
			uint16 serverID = fields[0].GetUInt16();
			uint8 count = fields[1].GetUInt16();
			Count c;
			c.m_count = count;
			counts[serverID] = c;
		}while(QR->NextRow());
	}
	delete QR;

	const World::GameServerStorageMap& servers = World::Instance().GetGameServers();
	std::vector<GameServerInformations> infos;
	for(World::GameServerStorageMap::const_iterator it = servers.begin(); it != servers.end(); ++it)
		infos.push_back(GetServerStatusMessage(it->second, counts[it->first].m_count));
	Send(ServersListMessage(infos));
}

void Session::InitHandlersTable()
{
	m_handlers[CMSG_IDENTIFICATION].Handler = &Session::HandleIdentificationMessage;
	m_handlers[CMSG_IDENTIFICATION].Flag = FLAG_NOT_CONNECTED;

	m_handlers[CMSG_SERVER_SELECTION].Handler = &Session::HandleServerSelectionMessage;
	m_handlers[CMSG_SERVER_SELECTION].Flag = FLAG_OUT_OF_QUEUE;

	m_handlers[CMSG_ACQUAINTANCE_SEARCH].Handler = &Session::HandleAcquaintanceSearchMessage;
	m_handlers[CMSG_ACQUAINTANCE_SEARCH].Flag = FLAG_OUT_OF_QUEUE;
}

Session::~Session()
{
}

void Session::Start()
{
	Send(ProtocolRequired(PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD));

	m_key = GenerateRandomKey();
	Send(HelloConnectMessage(0, m_key));

	Run();
}