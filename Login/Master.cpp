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

template<> Desperion::Master* Singleton<Desperion::Master>::m_singleton = NULL;

void SignalShutDown()
{
	Desperion::Master::Instance().ShutDown(SHUTDOWN_NORMAL);
}

namespace Desperion
{
	TypeErasureDatabase* sDatabase = NULL;

	Master::Master()
	{
		m_shutdown = SHUTDOWN_NOT_REQUESTED;
		InitRandomNumberGenerators();
		new ThreadPool(m_service);
		new DofusQueue;
	}

	Master::~Master()
	{
		CleanupRandomNumberGenerators();
		delete Config::InstancePtr();
		delete DofusQueue::InstancePtr();
		delete ThreadPool::InstancePtr();
		delete World::InstancePtr();
		delete sDatabase;
		delete Log::InstancePtr();
	}

	bool Master::StartUpDatabase()
	{
		sDatabase = ConstructDatabase(m_service,
			Config::Instance().GetParam(LOCAL_DATABASE_TYPE_STRING, LOCAL_DATABASE_TYPE_DEFAULT), 3);
		if(sDatabase == NULL)
		{
			Log::Instance().OutError("Local database: unknown database type");
			return false;
		}
		Log::Instance().OutNotice("Database", "Connecting to the local database...");
		if(!sDatabase->Init(Config::Instance().GetParam<std::string>(LOCAL_DATABASE_HOST_STRING, LOCAL_DATABASE_HOST_DEFAULT), 
			Config::Instance().GetParam(LOCAL_DATABASE_PORT_STRING, LOCAL_DATABASE_PORT_DEFAULT), 
			Config::Instance().GetParam<std::string>(LOCAL_DATABASE_USER_STRING, LOCAL_DATABASE_USER_DEFAULT), 
			Config::Instance().GetParam<std::string>(LOCAL_DATABASE_PASSWORD_STRING, LOCAL_DATABASE_PASSWORD_DEFAULT), 
			Config::Instance().GetParam<std::string>(LOCAL_DATABASE_NAME_STRING, LOCAL_DATABASE_NAME_DEFAULT)))
			return false;
		Log::Instance().OutNotice("Database", "Connection successful!\n\n");

		return true;
	}

	bool Master::LoadRSAPublicKey()
	{
		std::ifstream file(Config::Instance().GetParam<std::string>(PUB_FILE_PATH_STRING, PUB_FILE_PATH_DEFAULT).c_str(),
			std::ios::binary);
		if(!file)
			return false;
		file.seekg(0, std::ios_base::end);
		size_t size = file.tellg();
		PublicKey.resize(size);
		file.seekg(0, std::ios_base::beg);
		file.read((char*)&PublicKey[0], size);
		Log::Instance().OutNotice("Network", "RSA public key loaded");
		return true;
	}

	bool Master::LoadRSAPrivateKey()
	{
		try
		{
			CryptoPP::ByteQueue queue;
			CryptoPP::FileSource file(Config::Instance().GetParam<std::string>(PRIV_FILE_PATH_STRING, PRIV_FILE_PATH_DEFAULT).c_str(),
				true);
			file.TransferTo(queue);
			queue.MessageEnd();
			PrivateKey.Load(queue);
		}catch(const CryptoPP::Exception& e)
		{
			Log::Instance().OutError(e.what());
			return false;
		}
		Log::Instance().OutNotice("Network", "RSA private key loaded");
		return true;
	}

	ShutDownType Master::Run(int argc, char **argv)
	{
		new Config;
		std::vector<const char*> files;
		files.push_back("server.properties"), files.push_back("misc.properties");
		std::string path = "./config";
		if(argc >= 2)
			path = argv[1];
		Config::Instance().Init(path, files);

		new Log(m_service);
		Log::Instance().Init(Config::Instance().GetParam<std::string>(LOGS_PATH_STRING, LOGS_PATH_DEFAULT).c_str(),
			Config::Instance().GetParam<uint8>(LOGS_LEVEL_STRING, LOGS_LEVEL_DEFAULT));

		SetApplicationTitle("Desperion LoginServer v%u.%u.%u", LOGIN_VERSION_MAJOR, LOGIN_VERSION_MINOR, LOGIN_VERSION_REVISION);
		Log::Instance().OutColor(TBLUE, 	",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,");
		Log::Instance().OutColor(TBLUE, 	"| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||");
		Log::Instance().OutColor(TBLUE, 	"| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||");
		Log::Instance().OutColor(TBLUE, 	"| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||");
		Log::Instance().OutColor(TBLUE, 	"| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||");
		Log::Instance().OutColor(TBLUE, 	"`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'\n");
		Log::Instance().OutColor(TWHITE, "Dofus v%u.%u.%u.%u.%u.%u, protocol %u/%u", DOFUS_VERSION_MAJOR, 
			DOFUS_VERSION_MINOR, DOFUS_VERSION_RELEASE, DOFUS_VERSION_REVISION, DOFUS_VERSION_PATCH, DOFUS_VERSION_BUILD_TYPE,
			PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD);
		Log::Instance().OutColor(TWHITE, "LoginServer v%u.%u.%u", LOGIN_VERSION_MAJOR, LOGIN_VERSION_MINOR, LOGIN_VERSION_REVISION);
		Log::Instance().OutColor(TWHITE, "Shared v%u.%u.%u\n\n", SHARED_VERSION_MAJOR, SHARED_VERSION_MINOR, SHARED_VERSION_REVISION);
	
		if(!StartUpDatabase())
			return SHUTDOWN_NORMAL;

		new World;
		World::Instance().Init();
		
		SocketListener<Session> sListener(ThreadPool::Instance().GetService(),
			Config::Instance().GetParam(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		Log::Instance().OutNotice("Network", "Listening for Dofus clients on port %u",
			Config::Instance().GetParam(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		SocketListener<GameSession> eListener(ThreadPool::Instance().GetService(),
			Config::Instance().GetParam(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
		Log::Instance().OutNotice("Network", "Listening for game servers on port %u",
				Config::Instance().GetParam(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));

		if(!LoadRSAPublicKey())
		{
			Log::Instance().OutError("Failed to load RSA public key");
			return SHUTDOWN_NORMAL;
		}
		else if(!LoadRSAPrivateKey())
		{
			Log::Instance().OutError("Failed to load RSA private key");
			return SHUTDOWN_NORMAL;
		}
	
		std::cout<<std::endl;
		Log::Instance().OutString("Uptime: %ums", GetUpTime());
		Log::Instance().OutColor(TBLUE, "Type Ctrl+C to safely shutdown the server.\n");
		
		HookSignals();
		while(m_shutdown == SHUTDOWN_NOT_REQUESTED)
		{
			m_service.reset();
			ThreadPool::Instance().SpawnWorkerThreads();
			m_service.run();
			ThreadPool::Instance().ClearWorkerThreads();
		}
		UnHookSignals();
		return m_shutdown;
	}
}