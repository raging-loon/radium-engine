#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "core/config/Config.h"
#include "graphics/IDisplay.h"
#include "graphics/IRenderDriver.h"
#include "core/event/Events.h"
#include "core/event/EventSystem.h"

namespace radium
{

struct AppConfig
{

};

class Application
{
public:

	Application();
	~Application();


	bool init();


	void onResize(WindowResizeEvent* e);
	void onClose(WindowCloseEvent* e);
	//void onMouseMove();

private:
	Config m_cfgmgr;
	Ref<IDisplay> m_window;
	Ref<IRenderDriver> m_renderDriver;

	bool m_shouldRun;
};

} // radium


#endif // CORE_APPLICATION_APPLICATION_H_