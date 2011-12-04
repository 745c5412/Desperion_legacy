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

#ifndef __CONFIG__
#define __CONFIG__

namespace Desperion
{
	class Config : public Singleton<Config>
	{
	public:
		void Init(std::string, std::vector<std::string>&);
		Config();
		void ParseAll();
		
		template<class T> T GetParam(std::string index, T def)
		{
			ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
			if(it == m_configMap.end())
				return def;
			T value(def);
			FromString(it->second, value);
			return value;
		}

		const std::vector<std::string>& GetFiles() const
		{ return m_files; }
	private:
		bool ParseFile(std::string);

		std::vector<std::string> m_files;
		std::string m_path;
		typedef std::tr1::unordered_map<std::string, std::string> ConfigMap;
		ConfigMap m_configMap;
	};

	template<> inline bool Config::GetParam(std::string index, bool def)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
			if(it == m_configMap.end())
				return def;
		return ToLowerCase(it->second) != "false";
	}

	template<> inline std::string Config::GetParam(std::string index, std::string def)
	{
		ConfigMap::iterator it = m_configMap.find(ToLowerCase(index));
			if(it == m_configMap.end())
				return def;
		return it->second;
	}

}

#endif