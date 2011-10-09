#include "StdAfx.h"

int main(int argc, char *argv[])
{
#ifdef _WIN32
	HANDLE hLogFile;
	hLogFile = CreateFile("./memory_leaks.log", GENERIC_WRITE, 
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
#endif
	new Desperion::Master;
	Desperion::Master::Instance().Run(argc, argv);

	Log::Instance().outString("Desperion is shutting down...");
	delete Desperion::Master::InstancePtr();
	printf("Press any key to continue!");
	std::getchar();

	return 0;
}