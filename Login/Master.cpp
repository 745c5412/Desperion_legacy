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

void OnCrash();

namespace Desperion
{
	Database sDatabase(3);

	void OnSignal(int s)
	{
		switch (s)
		{
		case SIGINT:
		case SIGTERM:
		case SIGABRT:
#ifdef _WIN32
		case SIGBREAK:
#endif
			ThreadPool::Instance().GetIoService().stop();
			Master::Instance().MasterCondition.notify_all();
			break;
		}
		signal(s, OnSignal);
	}

	void HookSignals()
	{
		signal(SIGINT, OnSignal);
		signal(SIGTERM, OnSignal);
		signal(SIGABRT, OnSignal);
#ifdef _WIN32
		signal(SIGBREAK, OnSignal);
#else
		signal(SIGSEGV, ::OnCrash);
		signal(SIGFPE, ::OnCrash);
		signal(SIGILL, ::OnCrash);
		signal(SIGBUS, ::OnCrash);
#endif
	}

	void UnHookSignals()
	{
		signal(SIGINT, 0);
		signal(SIGTERM, 0);
		signal(SIGABRT, 0);
#ifdef _WIN32
		signal(SIGBREAK, 0);
#else
		signal(SIGSEGV, 0);
		signal(SIGFPE, 0);
		signal(SIGILL, 0);
		signal(SIGBUS, 0);
#endif
	}

	Master::Master() : m_startTime(getMSTime())
	{
		InitRandomNumberGenerators();
		new ThreadPool;
		new Config;
		new Log;
		new World;
	}

	Master::~Master()
	{
		CleanupRandomNumberGenerators();
		delete Desperion::Config::InstancePtr();
		delete Log::InstancePtr();
	}

	bool Master::StartUpDatabase()
	{
		Log::Instance().outNotice("Database", "Connecting to the local database...");
		{
			barGoLink bar(1);
			if(!sDatabase.Init(Config::Instance().GetParam<std::string>(LOCAL_DATABASE_HOST_STRING, LOCAL_DATABASE_HOST_DEFAULT), 
				Config::Instance().GetParam(LOCAL_DATABASE_PORT_STRING, LOCAL_DATABASE_PORT_DEFAULT), 
				Config::Instance().GetParam<std::string>(LOCAL_DATABASE_USER_STRING, LOCAL_DATABASE_USER_DEFAULT), 
				Config::Instance().GetParam<std::string>(LOCAL_DATABASE_PASSWORD_STRING, LOCAL_DATABASE_PASSWORD_DEFAULT), 
				Config::Instance().GetParam<std::string>(LOCAL_DATABASE_NAME_STRING, LOCAL_DATABASE_NAME_DEFAULT)))
				return false;
			bar.step();
		}
		Log::Instance().outNotice("Database", "Connection successful!\n\n");

		return true;
	}

	bool Master::Run(int argc, char **argv)
	{
		std::vector<const char*> files;
		files.push_back("server.properties"), files.push_back("misc.properties");
		std::string path = "./config";
		if(argc >= 2)
			path = argv[1];
		Config::Instance().Init(path, files);

		Log::Instance().Init(Config::Instance().GetParam<std::string>(LOGS_PATH_STRING, LOGS_PATH_DEFAULT),
			Config::Instance().GetParam<uint8>(LOGS_LEVEL_STRING, LOGS_LEVEL_DEFAULT));

		SetApplicationTitle("Desperion LoginServer v%u.%u.%u", LOGIN_VERSION_MAJOR, LOGIN_VERSION_MINOR, LOGIN_VERSION_REVISION);
		Log::Instance().outColor(TBLUE, 	",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,");
		Log::Instance().outColor(TBLUE, 	"| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||");
		Log::Instance().outColor(TBLUE, 	"| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||");
		Log::Instance().outColor(TBLUE, 	"`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'\n");
		Log::Instance().outColor(TWHITE, "Dofus v%u.%u.%u.%u.%u.%u, protocol %u/%u", DOFUS_VERSION_MAJOR, 
			DOFUS_VERSION_MINOR, DOFUS_VERSION_RELEASE, DOFUS_VERSION_REVISION, DOFUS_VERSION_PATCH, DOFUS_VERSION_BUILD_TYPE,
			PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD);
		Log::Instance().outColor(TWHITE, "LoginServer v%u.%u.%u", LOGIN_VERSION_MAJOR, LOGIN_VERSION_MINOR, LOGIN_VERSION_REVISION);
		Log::Instance().outColor(TWHITE, "Shared v%u.%u.%u\n\n", SHARED_VERSION_MAJOR, SHARED_VERSION_MINOR, SHARED_VERSION_REVISION);
	
		if(!StartUpDatabase())
			return false;

		World::Instance().Init();
		sListener.Init(Config::Instance().GetParam(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		if(sListener.IsOpen())
		{
			Log::Instance().outNotice("Network", "Local socket listening on port %u",
				Config::Instance().GetParam(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
			sListener.Run();
		}
		else
		{
			Log::Instance().outError("Error: Local socket");
			return false;
		}
		sListener.Run();
		eListener.Init(Config::Instance().GetParam(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
		if(eListener.IsOpen())
		{
			Log::Instance().outNotice("Network", "Distant socket listening on port %u",
				Config::Instance().GetParam(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
			eListener.Run();
		}
		else
		{
			Log::Instance().outError("Error: Distant socket");
			return false;
		}
	
		std::cout<<std::endl;
		Log::Instance().outString("Uptime: %ums", GetUpTime());
		Log::Instance().outColor(TBLUE, "Type Ctrl+C to safely shutdown the server.\n");
		
		HookSignals();
		boost::mutex::scoped_lock lock(m_mutex);
		while(!ThreadPool::Instance().GetIoService().stopped())
			MasterCondition.wait(lock);
		UnHookSignals();
		return true;
	}

}