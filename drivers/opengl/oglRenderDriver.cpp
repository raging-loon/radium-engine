#include "core/debug/Log.h"
#include "graphics/interface/IBuffer.h"
#include "graphics/interface/IShaderProgram.h"
#include "drivers/opengl/oglBuffer.h"


#include "oglTexture.h"
#include "oglRenderDriver.h"
#include "oglShaderFactory.h"
#include "oglShaderProgram.h"

#include "stb_image.h"

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

ITexture* radium::oglRenderDriver::createTexture(const char* path)
{
	int width, height, nChannels;

	unsigned char* imageData = stbi_load(path, &width, &height, &nChannels, 0);

	if (!imageData)
	{
		RAD_ENGINE_ERROR("Failed to load image at {}: {}", path, stbi_failure_reason());
		return nullptr;
	}
	
	GLuint texId;

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	oglTexture* nt = new oglTexture(texId, width, height);

	stbi_image_free(imageData);
	return nt;
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

