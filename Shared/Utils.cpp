#include "StdAfx.h"

using namespace std;

namespace Desperion
{
	
	void SetApplicationTitle(std::string title) // changer le titre de la console
	{
	#ifdef _WIN32
		title = "TITLE " + title;
		system(title.c_str());
	#else
		printf("\033]0;%s\007", title.c_str());
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
