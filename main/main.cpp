#include <cstdio>
#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "core/config/Hash.h"
#include "core/Variant.h"

#include <unordered_map>
#include <string.h>
#include <fstream>


int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr freeman");
	
	auto& cfgmgr = radium::Config::getSingleton();

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;
	RAD_ENGINE_INFO("Window Width: {}", cfgmgr["wwidth"]);

	return 0;

}