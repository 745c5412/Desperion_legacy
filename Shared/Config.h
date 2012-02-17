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

class Config : public Singleton<Config>
{
public:
	void Init(std::string, std::vector<const char*>&);
	Config();
	void ParseAll();
		
	template<class T> T GetParam(const std::string& index, const T& def)
	{
		ConfigMap::iterator it = m_configMap.find(Desperion::ToLowerCase(index));
		if(it == m_configMap.end())
			return def;
		T value(def);
		Desperion::FromString(it->second, value);
		return value;
	}

	const std::vector<const char*>& GetFiles() const
	{ return m_files; }
private:
	std::vector<const char*> m_files;
	std::string m_path;
	typedef std::tr1::unordered_map<std::string, std::string> ConfigMap;
	ConfigMap m_configMap;

	bool ParseFile(const char*);
};

template<> inline bool Config::GetParam(const std::string& index, const bool& def)
{
	ConfigMap::iterator it = m_configMap.find(Desperion::ToLowerCase(index));
		if(it == m_configMap.end())
			return def;
	return Desperion::ToLowerCase(it->second) != "false";
}

template<> inline std::string Config::GetParam(const std::string& index, const std::string& def)
{
	ConfigMap::iterator it = m_configMap.find(Desperion::ToLowerCase(index));
		if(it == m_configMap.end())
			return def;
	return it->second;
}

#endif