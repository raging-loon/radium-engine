#include "core/debug/Log.h"
#include "core/config/Config.h"

#include "graphics/IDisplay.h"

using namespace radium;

int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr. freeman");

	auto& cfgmgr = Config::getSingleton();

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;

	
	auto* window = IDisplay::createDisplay();

	window->create(
		cfgmgr["wwidth"],
		cfgmgr["wheight"],
		cfgmgr["windowed"],
		"don't forget to add title config"
	);

	window->show();

	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		window->processEvents();
	}


	delete window;
}