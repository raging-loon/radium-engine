#include "core/debug/Log.h"
#include "graphics/IBuffer.h"
#include "graphics/IShaderProgram.h"
#include "drivers/opengl/oglBuffer.h"

#include "oglRenderDriver.h"
#include "oglShaderFactory.h"

#include <GL/glew.h>
#include <GL/GL.h>

#include <filesystem>

using namespace radium;


oglRenderDriver::oglRenderDriver()
{

}

oglRenderDriver::~oglRenderDriver()
{
	terminate();
	
}

int oglRenderDriver::_int_init()
{
	auto err = glewInit();

	if (err != GLEW_OK)
	{
		RAD_ENGINE_CRITICAL("[GL] Failed to initialize GLEW: {}", (char*)glewGetErrorString(err));
		return -1;
	}

	RAD_ENGINE_INFO("[GL] Initialized GLEW: {}", (char*)glewGetString(GLEW_VERSION));

#ifdef RAD_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)oglRenderDriver::glErrorCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif // RAD_DEBUG
	
	glEnable(GL_DEPTH_TEST);


	return 0;
}

void oglRenderDriver::_int_terminate()
{
}


IBuffer* oglRenderDriver::createBuffer(BufferDescription& bd)
{
	return m_bufferFactory.createBuffer(bd);
}

ShaderID oglRenderDriver::createShader(ShaderProgramDescription& spd)
{
	return oglShaderFactory::createShaderProgram(spd);
}

void oglRenderDriver::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void oglRenderDriver::setViewport(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
}

void oglRenderDriver::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
