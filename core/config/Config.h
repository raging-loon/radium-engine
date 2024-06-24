#ifndef CORE_CONFIG_CONFIG_H_
#define CORE_CONFIG_CONFIG_H_

#include <unordered_map>
#include "core/Variant.h"
#include <string>



namespace radium
{

class Config
{
public:
	
	Variant& operator[](std::string k);

	void insert(std::string k, Variant value);

	bool loadConfig(const char* filename = nullptr);

public:
	static Config& getSingleton()
	{
		static Config s_config;
		return s_config;
	}


	Config(const Config&) = delete;
	Config(const Config&&) = delete;
	Config& operator=(const Config&) = delete;
	Config& operator=(const Config&&) = delete;

	~Config();


private:
	Config();
	
	bool readConfig(char* cfgBuf, size_t sz);
	bool parseLine(char* line);
	std::unordered_map < std::string , Variant > m_kvcfgmap;
};

}

#endif // CORE_CONFIG_CONFIG_H_