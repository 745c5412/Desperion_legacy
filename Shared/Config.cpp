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

	#define REALM_FILE_NUMBER 2
	#define GAME_FILE_NUMBER 3

	std::string _realm [] = {
			"server.properties",
			"misc.properties"
		};
		std::string _game [] = {
			"server.properties",
			"character.properties",
			"misc.properties"
		};

	Config::Config()
	{
		m_path = "";
	}

	void Config::Init(std::string path, uint8 target)
	{
		m_path = path;
		std::vector<std::string> errorTable;

		switch(target)
		{
		case TARGET_GAME:
			for(std::string * s = _game; s != _game + GAME_FILE_NUMBER; ++s)
				if(!ParseFile(*s))
					errorTable.push_back(*s);
			break;
		case TARGET_REALM:
			for(std::string * s = _realm; s != _realm + REALM_FILE_NUMBER; ++s)
				if(!ParseFile(*s))
					errorTable.push_back(*s);
			break;
		}
	
		for(uint8 a = 0; a < errorTable.size(); ++a)
			Log::Instance().outError("[WARNING] Config encountered at least one error while loading %s!", errorTable[a].c_str());
	}

	bool Config::ParseFile(std::string fileName)
	{
		std::string file = m_path + "/" + fileName;
		std::ifstream config(file.c_str(), std::ios::in);
		if(config.fail())
			return false;
		std::string line = ""; // Ligne à lire

		while(getline(config, line)) // On lit le fichier ligne par ligne
		{
			if(line.find("#") != std::string::npos)
				continue;

			std::vector<std::string> table;

			Split(table, line, '=');
			if(table.size() == 0 || table[0].empty())
				continue;

			std::string index = table [0];
			std::string value = (table.size() == 1 ? "" : table [1]);

			// On retire les espaces
			boost::trim(index);
			boost::trim(value);

			m_configMap[ToLowerCase(index)] = value;
		}
		config.close ();
		return true;
	}

	bool Config::GetBool(std::string index, bool value)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
		if(it == m_configMap.end ())
		{
			Log::Instance().outError("[Warning] Index %s doesn't exist!", index.c_str());
			return value;
		}
		return !(ToLowerCase(it->second) == "false");
	}

	std::string Config::GetString(std::string index, std::string value)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
		if(it == m_configMap.end())
		{
			Log::Instance().outError("[Warning] Index %s doesn't exist!", index.c_str());
			return value;
		}
		return it->second;
	}

	int64 Config::GetInt(std::string index, int64 value)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
		if (it == m_configMap.end() || it->second.empty())
		{
			Log::Instance().outError("[Warning] Index %s doesn't exist or is empty!", index.c_str());
			return value;
		}
		
		int64 found = value;
		FromString(it->second, found);
		return found;
	}

	uint64 Config::GetUInt(std::string index, uint64 value)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
		if (it == m_configMap.end() || it->second.empty())
		{
			Log::Instance().outError("[Warning] Index %s doesn't exist or is empty!", index.c_str());
			return value;
		}
		uint64 found = value;
		FromString(it->second, found);
		return found;
	}

}