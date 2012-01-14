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

template<> Desperion::Config* Singleton<Desperion::Config>::m_singleton = NULL;

namespace Desperion
{
	Config::Config() : m_path("./")
	{
	}

	void Config::Init(std::string path, std::vector<const char*>& files)
	{
		m_path = path;
		m_files = files;
		ParseAll();
	}

	void Config::ParseAll()
	{
		for(std::vector<const char*>::iterator it = m_files.begin(); it != m_files.end(); ++it)
		{
			if(!ParseFile(*it))
				std::cerr<<"Parsing failed: "<<*it<<std::endl;
		}
	}

	bool Config::ParseFile(const char* fileName)
	{
		std::string file = m_path + "/" + fileName;
		std::ifstream config(file.c_str(), std::ios::in);
		if(config.fail())
			return false;
		std::string line = "";

		while(getline(config, line))
		{
			if(line.find("#") != std::string::npos)
				continue;

			std::vector<std::string> table;

			FastSplitString<'='>(table, line, true);
			if(table.size() == 0 || table[0].empty())
				continue;

			std::string index = table[0];
			std::string value = (table.size() == 1 ? "" : table[1]);

			boost::trim(index);
			boost::trim(value);

			m_configMap[ToLowerCase(index)] = value;
		}
		config.close ();
		return true;
	}
}