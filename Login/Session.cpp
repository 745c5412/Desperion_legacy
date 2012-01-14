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
	ResultPtr QR = Desperion::sDatabase.Query("SELECT banEnd FROM ip_bans WHERE IP='%s' LIMIT 1;", address.c_str());
	if(!QR)
		return false;
	Field* fields = QR->Fetch();
	time_t banEnd = fields[0].GetInt64();

	if(banEnd < time(NULL))
	{
		Desperion::sDatabase.Execute("DELETE FROM ip_bans WHERE IP='%s' LIMIT 1;", address.c_str());
		return false;
	}
	else
		return true;
}

void Session::LOG(const char* str, ...)
{
	if(m_data[FLAG_GUID].intValue == 0 || !str)
		return;

	if(!m_logs)
	{
		std::ostringstream fileName;
		fileName<<"sessions/"<<m_data[FLAG_GUID].intValue<<".log";
		m_logs.open(fileName.str().c_str(), std::ios::app);
	}

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

	Log::Instance().outFile(m_logs, std::string(buf));
}

void Session::HandleAcquaintanceSearchMessage(ByteBuffer& packet)
{
	AcquaintanceSearchMessage data;
	data.Deserialize(packet);

	const char* query = "SELECT serverID FROM character_counts INNER JOIN accounts ON accounts.guid = character_counts.accountGuid "\
		"WHERE LOWER(accounts.pseudo)='%s';";
	ResultPtr QR = Desperion::sDatabase.Query(query,
		Desperion::ToLowerCase(Desperion::sDatabase.EscapeString(data.nickname)).c_str());
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
			Send(SelectedServerRefusedMessage(G->GetID(), reason, state));
		return false;
	}
	//todo: restriction de communauté et de géolocalisation
	
	std::string ticket = GenerateRandomKey();
	if(!Desperion::sDatabase.Execute("UPDATE accounts SET ticket='%s' WHERE guid=%u LIMIT 1;", ticket.c_str(), m_data[FLAG_GUID].intValue))
	{
		if(!quiet)
			Send(SelectedServerRefusedMessage(G->GetID(), SERVER_CONNECTION_ERROR_NO_REASON, state));
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

	HandleServerSelection(World::Instance().GetGameServer(data.serverId), false);
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
	ResultPtr QR = Desperion::sDatabase.Query("SELECT serverID FROM character_counts WHERE accountGuid=%u;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		do
		{
			Field* fields = QR->Fetch();
			++counts[fields[0].GetUInt16()].count;
		}while(QR->NextRow());
	}
	

	const World::GameServerMap& servers = World::Instance().GetGameServers();
	std::vector<GameServerInformationsPtr> infos;
	for(World::GameServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it)
		infos.push_back(GameServerInformationsPtr(GetServerStatusMessage(it->second, counts[it->first].count)));
	Send(ServersListMessage(infos));
}

void Session::HandleIdentificationMessage(ByteBuffer& packet)
{
	IdentificationMessage data;
	data.Deserialize(packet);

	if(Desperion::Config::Instance().GetParam(SERVER_MAINTENANCE_STRING, SERVER_MAINTENANCE_DEFAULT))
	{
		Send(IdentificationFailedMessage(IN_MAINTENANCE));
		m_socket->close();
		return;
	}
	else if(IsIpBanned(m_socket->remote_endpoint().address().to_string()))
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		m_socket->close();
		return;
	}
	else if(!VerifyVersion(*(data.version)))
	{
		Send(IdentificationFailedForBadVersionMessage(BAD_VERSION, new Version(DOFUS_VERSION_MAJOR, DOFUS_VERSION_MINOR, DOFUS_VERSION_RELEASE,
			DOFUS_VERSION_REVISION, DOFUS_VERSION_PATCH, DOFUS_VERSION_BUILD_TYPE)));
		m_socket->close();
		return;
	}

	const char* query = "SELECT password, guid, question, pseudo, logged, level, lastServer, subscriptionEnd, banEnd FROM accounts \
						WHERE LOWER(account)='%s' LIMIT 1;";
	ResultPtr QR = Desperion::sDatabase.Query(query, Desperion::ToLowerCase(Desperion::sDatabase.EscapeString(data.login)).c_str());
	
	if(!QR)
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		m_socket->close();
		return;
	}

	std::string result;
	try
	{
		CryptoPP::ByteQueue queue;
		CryptoPP::FileSource file(Desperion::Config::Instance().GetParam<std::string>(PRIV_FILE_PATH_STRING, PRIV_FILE_PATH_DEFAULT).c_str(),
			true);
		file.TransferTo(queue);
		queue.MessageEnd();
		CryptoPP::RSA::PrivateKey privateKey;
		privateKey.Load(queue);
		CryptoPP::RSAES_PKCS1v15_Decryptor d(privateKey);
		CryptoPP::AutoSeededRandomPool rng;
		CryptoPP::StringSource((uint8*)&data.credentials[0], data.credentials.size(), true,
			new CryptoPP::PK_DecryptorFilter(rng, d, new CryptoPP::StringSink(result)));
		result = data.useCertificate ? result.substr(m_salt.size() + 2 + 66) : result.substr(m_salt.size());
	}
	catch(...)
	{
		Send(IdentificationFailedMessage(UNKNOWN_AUTH_ERROR));
		m_socket->close();
		return;
	}

	Field* fields = QR->Fetch();
	if(std::istring(fields[0].GetString()) != Desperion::ComputeMD5Digest(result))
	{
		Send(IdentificationFailedMessage(WRONG_CREDENTIALS));
		m_socket->close();
		return;
	}
	
	int guid = fields[1].GetUInt32();
	time_t banEnd = fields[8].GetUInt64();
	if(banEnd < time(NULL))
		Desperion::sDatabase.Execute("UPDATE accounts SET banEnd=0 WHERE guid=%u LIMIT 1;", guid);
	else
	{
		Send(IdentificationFailedBannedMessage(BANNED, banEnd));
		m_socket->close();
		return;
	}

	uint16 logged = fields[4].GetUInt16();
	bool alreadyConnected = false;
	Session* S = World::Instance().GetSession(guid);
	if(S != NULL)
	{
		alreadyConnected = true;
		S->GetSocket()->close();
	}
	else if(logged != 0)
	{
		GameSession* G = World::Instance().GetGameSession(logged);
		if(G != NULL)
		{
			G->SendDisconnectPlayerMessage(guid);
			alreadyConnected = true;
		}
		else if(World::Instance().GetGameServer(logged) != NULL)
		{
			Send(IdentificationFailedMessage(SPARE));
			return;
		}
	}

	m_subscriptionEnd = fields[7].GetUInt64();
	m_data[FLAG_LAST_SERVER].intValue = fields[6].GetUInt16();
	m_data[FLAG_PSEUDO].stringValue = fields[3].GetString();
	m_data[FLAG_GUID].intValue = guid;
	m_data[FLAG_LEVEL].intValue = fields[5].GetUInt8();
	m_data[FLAG_QUESTION].stringValue = fields[2].GetString();
	m_data[FLAG_ACCOUNT].stringValue = data.login;
	

	World::Instance().AddSession(this);
	LOG("***** Connection with IP address %s {%s} *****", m_socket->remote_endpoint().address().to_string().c_str(),
		Desperion::FormatTime("%x").c_str());

	Send(IdentificationSuccessMessage(m_data[FLAG_LEVEL].intValue > 0, alreadyConnected, data.login, m_data[FLAG_PSEUDO].stringValue,
		m_data[FLAG_GUID].intValue, 0, m_data[FLAG_QUESTION].stringValue, m_subscriptionEnd));
	
	if(data.autoconnect)
	{
		if(HandleServerSelection(World::Instance().GetGameServer(m_data[FLAG_LAST_SERVER].intValue), true))
			return;
	}
	else if(data.serverId > 0)
	{
		if(HandleServerSelection(World::Instance().GetGameServer(data.serverId), true))
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
}

Session::~Session()
{
	if(m_data[FLAG_GUID].intValue != 0)
	{
		World::Instance().DeleteSession(m_data[FLAG_GUID].intValue);
		LOG("***** Disconnection *****");
	}
}

void Session::Start()
{
	Send(ProtocolRequired(PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD));

	std::ifstream file(Desperion::Config::Instance().GetParam<std::string>(PUB_FILE_PATH_STRING, PUB_FILE_PATH_DEFAULT).c_str(),
		std::ios::binary);

	if(!file)
		throw std::runtime_error("*** ERROR: PUBLIC KEY FILE DOESN'T EXIST! ***");
	
	std::vector<int8> bytes;
	char c;
	while(file.get(c))
		bytes.push_back(c);
	m_salt = GenerateRandomKey();
	Send(HelloConnectMessage(m_salt, bytes));
	
	Run();
}