#include "oglBufferFactory.h"
#include "core/debug/Log.h"
#include "oglBuffer.h"
#include "graphics/VertexData.h"

#include <GL/glew.h>

using namespace radium;

oglBuffer* oglBufferFactory::createBuffer(BufferDescription& bd)
{
	GLuint id		= GL_INVALID_VALUE;
	GLuint vaoID	= GL_INVALID_VALUE;
	GLenum target	= GL_INVALID_ENUM;

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

	oglBuffer* nbuf = new oglBuffer(id, target, bd.type, vaoID);

	nbuf->copyData(bd.count * bd.size, bd.data);
	
	nbuf->unbind();
	
	return nbuf;
}

int oglBufferFactory::createIndexBuffer(BufferDescription& bd, GLuint& id)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	return 0;
}

int oglBufferFactory::createVertexBuffer(BufferDescription& bd, GLuint& id, GLuint& vaoID)
{
	glGenVertexArrays(1, &vaoID);

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	// format data

	// position (vec3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
	glEnableVertexAttribArray(0);

	return 0;
}
