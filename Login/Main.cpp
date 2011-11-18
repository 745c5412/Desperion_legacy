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

void OnCrash()
{
	std::cout<<"********* FATAL ERROR *********"<<std::endl;
	std::cout<<"Press any key for termination."<<std::endl;
	std::getchar();
}

int main(int argc, char *argv[])
{
#ifdef _MSC_VER
	HANDLE hLogFile;
	hLogFile = CreateFile("./memory_leaks.log", GENERIC_WRITE, 
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);

	if(!CheckForDebugger())
	{
		rde::CrashHandler::Init();
		rde::CrashHandler::SetCrashHandler(&OnCrash);
	}
#endif
	new Desperion::Master;
	
	if(Desperion::Master::Instance().Run(argc, argv))
		Log::Instance().outString("Desperion is shutting down...");
	else
		Log::Instance().outError("Abnormal Desperion termination!");

	delete Desperion::Master::InstancePtr();
	delete Desperion::Config::InstancePtr();
	delete World::InstancePtr();
	delete Desperion::sDatabase;
	delete Log::InstancePtr();

	std::cout<<"Press any key to continue!"<<std::endl;
	std::getchar();

	return 0;
}