#include "GLRenderDriver.h"
#include "core/debug/Log.h"

#include <GL/glew.h>
#include <GL/GL.h>

using radium::glRenderDriver;

glRenderDriver::glRenderDriver()
{

}

glRenderDriver::~glRenderDriver()
{
	terminate();
}

int glRenderDriver::init()
{
	auto err = glewInit();

	if (err != GLEW_OK)
	{
		RAD_ENGINE_CRITICAL("Failed to initialize GLEW: {}", (char*)glewGetErrorString(err));
		return -1;
	}

	RAD_ENGINE_INFO("Initialized GLEW: {}", (char*)glewGetString(GLEW_VERSION));

#ifdef RAD_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)glRenderDriver::glErrorCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER,1, GL_DEBUG_SEVERITY_NOTIFICATION, 22, "Debug Context Created");
#endif // RAD_DEBUG

	return 0;
}

void glRenderDriver::terminate()
{
	
}
