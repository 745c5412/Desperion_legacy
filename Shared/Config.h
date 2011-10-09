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