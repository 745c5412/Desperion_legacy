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
#include "../CacheDataExploiter/StdAfx.h"

template<> Desperion::Master* Singleton<Desperion::Master>::m_singleton = NULL;

namespace Desperion
{
	Database* sDatabase = NULL;
	Database* eDatabase = NULL;

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
			Master::Instance().Stop();
			break;
		}
		signal(s, OnSignal);
	}

	void HookSignals()
	{
		signal( SIGINT, OnSignal );
		signal( SIGTERM, OnSignal );
		signal( SIGABRT, OnSignal );
	#ifdef _WIN32
		signal( SIGBREAK, OnSignal );
	#endif
	}

	void UnHookSignals()
	{
		signal( SIGINT, 0 );
		signal( SIGTERM, 0 );
		signal( SIGABRT, 0 );
	#ifdef _WIN32
		signal( SIGBREAK, 0 );
	#endif
	}

	Master::~Master()
	{
		CleanupRandomNumberGenerators();
		delete sListener;
	}

	bool Master::StartUpDatabase()
	{
		Log::Instance().outNotice("Database", "Connecting to the local database...");
		{
			barGoLink bar(1);
			sDatabase = new Database(3);
			if(!sDatabase->Init(Config::Instance().GetString(LOCAL_DATABASE_HOST_STRING, LOCAL_DATABASE_HOST_DEFAULT), 
				Config::Instance().GetUInt(LOCAL_DATABASE_PORT_STRING, LOCAL_DATABASE_PORT_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_USER_STRING, LOCAL_DATABASE_USER_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_PASSWORD_STRING, LOCAL_DATABASE_PASSWORD_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_NAME_STRING, LOCAL_DATABASE_NAME_DEFAULT)))
				return false;
			bar.step();
		}
		Log::Instance().outNotice("Database", "Connection successful!\n\n");

		Log::Instance().outNotice("Database", "Connecting to the distant database...");
		{
			barGoLink bar(1);
			eDatabase = new Database(1);
			if(!eDatabase->Init(Config::Instance().GetString(DISTANT_DATABASE_HOST_STRING, DISTANT_DATABASE_HOST_DEFAULT), 
				Config::Instance().GetUInt(DISTANT_DATABASE_PORT_STRING, DISTANT_DATABASE_PORT_DEFAULT), 
				Config::Instance().GetString(DISTANT_DATABASE_USER_STRING, DISTANT_DATABASE_USER_DEFAULT), 
				Config::Instance().GetString(DISTANT_DATABASE_PASSWORD_STRING, DISTANT_DATABASE_PASSWORD_DEFAULT), 
				Config::Instance().GetString(DISTANT_DATABASE_NAME_STRING, DISTANT_DATABASE_NAME_DEFAULT)))
				return false;
			bar.step();
		}
		Log::Instance().outNotice("Database", "Connection successful!\n\n");

		return true;
	}

	bool Master::Run(int argc, char **argv)
	{
		std::string logPath = "logs";
		std::string configPath = "config";
		std::string logFlags = "0";

		m_startTime = getMSTime();

		new Log;
		Log::Instance().Init(logPath, OUTLOG_ALL);

		InitRandomNumberGenerators();

		SetApplicationTitle("Desperion2 GameServer v" + m_version);
		Log::Instance().outColor(TBLUE, 	",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,");
		Log::Instance().outColor(TBLUE, 	"| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||");
		Log::Instance().outColor(TBLUE, 	"| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||");
		Log::Instance().outColor(TBLUE, 	"`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'");
		Log::Instance().outColor(TBLUE, "By Little-scaraby for Dofus 2.0\n\n");
		Log::Instance().outColor(TBLUE, "GameServer v%s\n\n\n", m_version.c_str());
	
		new Config;
		Config::Instance().Init(configPath, TARGET_GAME);

		if(!StartUpDatabase())
			return false;

		/*new D2oFileAccessor;
		sFileAccessor.Init(".");
		D2oFile* file = sFileAccessor.LoadFile("ItemSets.d2o");
		typedef std::vector<std::pair<D2oClassDefinition, Data> > Result;
		Result result = file->ReadAllData();
		barGoLink go(result.size());
		for(Result::iterator it = result.begin(); it != result.end(); ++it)
		{
			std::vector<std::vector<Data> > effects = DoubleVectorCast<Data>(it->second["effects"]);
			std::ostringstream e;
			e<<(effects.size() - 1);
			for(int a = 1; a < effects.size(); ++a)
			{
				if(effects[a].empty())
					continue;
				e<<":";
				if(effects[a][0].GetClassID() != 2)
				{
					e<<0;
					continue;
				}
				e<<effects[a].size();
				for(int b = 0; b < effects[a].size(); ++b)
				{
					e<<";";
					e<<8<<","<<DataCast<int>(effects[a][b]["targetId"])<<","<<DataCast<bool>(effects[a][b]["hidden"])<<",";
					e<<DataCast<int>(effects[a][b]["effectId"])<<","<<DataCast<int>(effects[a][b]["duration"])<<",";
					e<<DataCast<int>(effects[a][b]["random"])<<","<<DataCast<int>(effects[a][b]["zoneSize"])<<",";
					e<<DataCast<int>(effects[a][b]["value"])<<","<<DataCast<int>(effects[a][b]["zoneShape"]);
				}
			}
			sDatabase->Execute("UPDATE d2o_item_set SET effects='%s' WHERE id=%u LIMIT 1;", e.str().c_str(),
				DataCast<int>(it->second["id"]));
			go.step();
		}
		delete D2oFileAccessor::InstancePtr();
		return true;*/

		new World;
		World::Instance().Init();

		sListener = new SocketListener<Session>(m_service);
		sListener->Init(Config::Instance().GetUInt(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		if(sListener->IsOpen())
			Log::Instance().outNotice("Network", "Local socket running!\n");
		else
		{
			Log::Instance().outError("Error: Local socket");
			return false;
		}

		boost::shared_ptr<GameClient> ptr(new GameClient);
		GameClient::Instance().Init(new Socket(m_service));

		Log::Instance().outColor(TBLUE, "Uptime: %ums", getMSTime() - m_startTime);
		Log::Instance().outColor(TBLUE, "Type Ctrl+C to safely shutdown the server.\n");

		sListener->Run();
		GameClient::Instance().Launch();

		HookSignals();
		try
		{
			m_service.run();
		}catch(const std::exception& err)
		{
			Log::Instance().outError("Unhandled exception: %s", err.what());
		}
		UnHookSignals();

		GameClient::Instance().Stop();
		return true;
	}

}