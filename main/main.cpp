#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "core/config/Hash.h"
#include "core/Variant.h"
#include "graphics/IDisplay.h"
#include "platform/win32/Win32Display.h"
#include "drivers/opengl/oglRenderDriver.h"


#include <cstdio>
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

	radium::IDisplay* test = new radium::win32::Win32Display();

	test->create(
		cfgmgr["wwidth"], cfgmgr["wheight"],
		cfgmgr["windowed"],
		"don't forget to add a config"
	);
	
	radium::RenderAPI api = static_cast<radium::RenderAPI>((int)cfgmgr["api"]);

	test->createGLContext();
	
	radium::IRenderDriver* rd = nullptr;
	
	if (api == radium::RenderAPI::OPENGL)
	{
		rd = new radium::oglRenderDriver;
	}

	rd->init();
	test->show();
	test->destroy();

	return 0;

}