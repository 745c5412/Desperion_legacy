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

using namespace std;

namespace Desperion
{
	
	void SetApplicationTitle(const char* str, ...) // changer le titre de la console
	{
		char title[255];
		va_list vlist;
		va_start(vlist, str);
		vsnprintf(title, 255, str, vlist);
		va_end(vlist);

	#ifdef _WIN32
		char command[255 + 6] = "TITLE ";
		strcat(command, title);
		system(command);
	#else
		printf("\033]0;%s\007", title);
	#endif
	}

	void Split(std::vector<std::string>& vector, std::string str, char sep)
	{
		vector.clear();

		istringstream iss(str);
		std::string cut;
		while(std::getline(iss, cut, sep))
			vector.push_back(cut);
	}

	int IndexOf(std::string c1, char c2)
	{
		for(uint32 a = 0; a < c1.size(); a++)
		{
			if(c1.at(a) == c2)
				return a;
		}
		return -1;
	}

	std::string ToUpperCase(std::string str)
	{
		std::string buffer = "";
		for(uint32 i = 0; i < str.size(); ++i)
			buffer += std::toupper(str.at(i));
		return buffer;
	}

	std::string ToLowerCase(std::string str)
	{	
		std::string buffer = "";
		for(uint32 i = 0; i < str.size(); ++i)
			buffer += std::tolower(str.at(i));
		return buffer;
	}
}
