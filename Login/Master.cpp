#include "StdAfx.h"

template<> Desperion::Master* Singleton<Desperion::Master>::m_singleton = NULL;

namespace Desperion
{
	Database* sDatabase = NULL;

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
	
		delete Config::InstancePtr();
		delete sListener;
		delete eListener;
		delete World::InstancePtr();
		delete sDatabase;
		delete Log::InstancePtr();
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

		SetApplicationTitle("Desperion2 LoginServer v" + m_version);
		Log::Instance().outColor(TBLUE, 	",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,");
		Log::Instance().outColor(TBLUE, 	"| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||");
		Log::Instance().outColor(TBLUE, 	"| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||");
		Log::Instance().outColor(TBLUE, 	"`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'");
		Log::Instance().outColor(TBLUE, "By Little-scaraby for Dofus 2.0\n\n");
		Log::Instance().outColor(TBLUE, "LoginServer v%s\n\n\n", m_version.c_str());
	
		new Config;
		Config::Instance().Init(configPath, TARGET_REALM);

		if(!StartUpDatabase())
			return false;

		new World;
		World::Instance().Init();
	
		boost::asio::io_service ios;

		sListener = new SocketListener<Session>(ios);
		sListener->Init(Config::Instance().GetUInt(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		if(sListener->IsOpen())
			Log::Instance().outNotice("Network", "Local socket running!\n");
		else
		{
			Log::Instance().outError("Error: Local socket");
			return false;
		}

		eListener = new SocketListener<GameSession>(ios);
		eListener->Init(Config::Instance().GetUInt(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
		if(eListener->IsOpen())
			Log::Instance().outNotice("Network", "Distant socket running!\n");
		else
		{
			Log::Instance().outError("Error: Distant socket");
			return false;
		}
	
		Log::Instance().outColor(TBLUE, "Uptime: %ums", getMSTime() - m_startTime);
		Log::Instance().outColor(TBLUE, "Type Ctrl+C to safely shutdown the server.\n");

		sListener->Run();
		eListener->Run();

		m_running = true;
		HookSignals();
		boost::posix_time::time_duration td = boost::posix_time::milliseconds(100);
		boost::thread(boost::bind(&boost::asio::io_service::run, &ios));
		while(m_running)
		{
			World::Instance().Update();
			boost::this_thread::sleep(td);
		}
		ios.stop();
		UnHookSignals();
		return true;
	}

}