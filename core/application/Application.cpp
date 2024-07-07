#include "Application.h"
#include "core/event/EventSystem.h"
#include "core/debug/Log.h"
using namespace radium;

Application::Application()
	: m_cfgmgr{},
	  m_window(nullptr), 
	  m_renderDriver(nullptr),
	  m_shouldRun(false)
{
	
}

Application::~Application()
{
}

bool Application::init()
{
	Log::init();
	RAD_ENGINE_INFO("hello mr. freeman");

	if (!m_cfgmgr.loadConfig("tests/engine.ini"))
	{
		RAD_ENGINE_ERROR("Failed to load config!");
		return false;
	}

	m_window = IDisplay::createDisplay();

	auto test = [this](auto&&... args) -> void
	{
		this->onResize(std::forward<decltype(args)>(args)...);
	};


	m_window->setWindowResizeCallback(
		bind_event_callback(this, &Application::onResize)
	);

	if (!m_window)
		return false;

	int res = m_window->create(
		m_cfgmgr["wwidth"],
		m_cfgmgr["wheight"],
		m_cfgmgr["windowed"],
		"don't forget to add title config"
	);

	if (res == -1)
		return false;

	auto driverConfig = m_window->createRenderDriverConfig();
	
	m_renderDriver = IRenderDriver::createRenderDriver(
		static_cast<RenderAPI>((int)m_cfgmgr["api"])
	);

	if (!m_renderDriver)
		return false;

	if (!m_renderDriver->init(driverConfig))
		return false;

	m_renderDriver->setClearColor(0, 0, 0, 1);
	m_renderDriver->setViewport(
		0,0,
		m_cfgmgr["wwidth"],
		m_cfgmgr["wheight"]
	);

	

	return true;
}


void Application::onResize(WindowResizeEvent* e)
{
	RAD_ENGINE_INFO("Resize Event: ({}, {})", e->newWidth, e->newHeight);
}

void Application::onClose(WindowCloseEvent* e)
{
}
