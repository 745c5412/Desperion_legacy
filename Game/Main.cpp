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
	if(World::InstancePtr() != NULL)
	{
		std::cout<<"CrashHandler: Desperion will try to save all players data. It can take very long time,";
		std::cout<<" and will necessarily abort if an error occurs."<<std::endl;
		World::Instance().SaveAll();
		std::cout<<"Save finished."<<std::endl;
		Desperion::sDatabase->Execute("DELETE FROM \"character_items\" WHERE \"owner\"=-1;");
	}
	std::cout<<"Press [ENTER] for termination."<<std::endl;
	std::getchar();
}

struct foo
{
	std::vector<int> a;

	foo()
	{ }

	foo(const std::vector<int>& a) : a(a)
	{ }
};

struct foo2
{
	std::vector<int> a;

	foo2()
	{ }

	foo2(std::vector<int>&& a) : a(a)
	{ }
};

int main(int argc, char **argv)
{
#ifdef _MSC_VER
	if(!CheckForDebugger())
	{
		rde::CrashHandler::Init();
		rde::CrashHandler::SetCrashHandler(&OnCrash);
	}
#endif
	ShutDownType s = SHUTDOWN_REBOOT;
	while(s == SHUTDOWN_REBOOT)
	{
		new Desperion::Master;
		s = Desperion::Master::Instance().Run(argc, argv);
		delete Desperion::Master::InstancePtr();
	}
	std::cout<<"Press [ENTER] to continue!"<<std::endl;
	std::getchar();
	return 0;
}