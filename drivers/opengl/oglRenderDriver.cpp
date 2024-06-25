#include "oglRenderDriver.h"
#include "core/debug/Log.h"
#include "graphics/IBuffer.h"
#include "drivers/opengl/oglBuffer.h"

#include <GL/glew.h>
#include <GL/GL.h>

using radium::oglRenderDriver;
using radium::BufferDescription;
using radium::IBuffer;
using radium::oglBuffer;

oglRenderDriver::oglRenderDriver()
{

}

oglRenderDriver::~oglRenderDriver()
{
	terminate();
	
}

int oglRenderDriver::init()
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
	glDebugMessageCallback((GLDEBUGPROC)oglRenderDriver::glErrorCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif // RAD_DEBUG

	return 0;
}

void oglRenderDriver::terminate()
{
	
}


IBuffer* oglRenderDriver::createBuffer(BufferDescription& bd)
{
	return m_bufferFactory.createBuffer(bd);
}
