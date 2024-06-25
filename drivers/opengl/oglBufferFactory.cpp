#include "oglBufferFactory.h"
#include "core/debug/Log.h"
#include "oglBuffer.h"
#include <GL/glew.h>

using namespace radium;

oglBuffer* oglBufferFactory::createBuffer(BufferDescription& bd)
{
	GLuint id = GL_INVALID_ENUM;
	GLuint vaoID = GL_INVALID_ENUM;
	GLenum target = GL_INVALID_ENUM;

	int bufCreateStatus = 0;

	switch (bd.type) {
	
		case buffer_t::VERTEX:
			bufCreateStatus = createVertexBuffer(bd, id, vaoID);
			target = GL_ARRAY_BUFFER;
			break;
		
		case buffer_t::INDEX:
			bufCreateStatus = createIndexBuffer(bd, id);
			target = GL_ELEMENT_ARRAY_BUFFER;
			break;

		default:
			RAD_ENGINE_ERROR("[GL] Failed to create buffer. Unknown type: {}", (int)bd.type);
			return nullptr;
	}

	oglBuffer* nbuf = new oglBuffer(id, target, vaoID);


	return nbuf;
}

int oglBufferFactory::createIndexBuffer(BufferDescription& bd, GLuint& id)
{
	return 0;
}

int oglBufferFactory::createVertexBuffer(BufferDescription& bd, GLuint& id, GLuint& vaoID)
{
	glGenVertexArrays(1, &vaoID);

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	if (bd.data)
	{
		glBufferData(
			GL_ARRAY_BUFFER,
			bd.size * bd.count,
			bd.data,
			GL_STATIC_DRAW
		);
	}



	return 0;
}
