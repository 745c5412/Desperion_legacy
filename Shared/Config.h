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

#ifndef __CONFIG__
#define __CONFIG__

#define TARGET_GAME 0
#define TARGET_REALM 1

namespace Desperion
{
	class Config : public Singleton<Config>
	{
	public:
		void Init(std::string, uint8);
		Config();
		bool ParseFile(std::string);
		std::string GetString(std::string, std::string);
		int64 GetInt(std::string, int64);
		uint64 GetUInt(std::string, uint64);
		bool GetBool(std::string, bool);
	private:
		std::string m_path;
		typedef std::tr1::unordered_map<std::string, std::string> ConfigMap;
		ConfigMap m_configMap;
	};

}

#endif