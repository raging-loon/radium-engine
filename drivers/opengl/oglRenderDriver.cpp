#include "core/debug/Log.h"
#include "graphics/IBuffer.h"
#include "graphics/IShaderProgram.h"
#include "drivers/opengl/oglBuffer.h"

#include "oglRenderDriver.h"
#include "oglShaderFactory.h"
#include "oglShaderProgram.h"

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

IShaderProgram* oglRenderDriver::createShader(ShaderProgramDescription& spd)
{

	auto sid = oglShaderFactory::createShaderProgram(spd);
	if (sid == -1)
		return nullptr;
	return new oglShaderProgram(sid);
	
}

void oglRenderDriver::draw(IShaderProgram* shader, RenderItem* drawList, U32 dlSize)
{
	//auto sp = ((oglShaderProgram*)shader);
	//glUseProgram(((oglShaderProgram*)shader)->m_shaderID);
	//
	//glBindBufferRange(GL_UNIFORM_BUFFER, 3, sp->m_perPassUB, 0, sp->m_perPassItemSize);

	//for (U32 i = 0; i < dlSize; i++)
	//{
	//	RenderItem* cur = &drawList[i];
	//	oglBuffer* idxb = (oglBuffer*)cur->indexBuffer;
	//	oglBuffer* vtxb = (oglBuffer*)cur->vertexBuffer;
	//	
	//	vtxb->bindVAO();
	//	vtxb->bind();
	//	idxb->bind();

	//	glBindBufferRange(GL_UNIFORM_BUFFER, 2, sp->m_perObjectUB, cur->uniformIndex * sp->m_perObjectItemSize, sp->m_perObjectItemSize);
	//	glDrawElements(GL_TRIANGLES, idxb->count, GL_UNSIGNED_INT, nullptr);
	//}

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

