#include "oglBufferFactory.h"
#include "core/debug/Log.h"
#include "oglBuffer.h"
#include "graphics/component/VertexData.h"

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
		
		case buffer_t::UNIFORM:
			createUniformBuffer(bd, id, bd.binding);
			target = GL_UNIFORM_BUFFER;
			break;
		default:
			RAD_ENGINE_ERROR("[GL] Failed to create buffer. Unknown type: {}", (int)bd.type);
			return nullptr;
	}

	assert(id != GL_INVALID_VALUE);
	assert(target != GL_INVALID_ENUM);
	oglBuffer* nbuf = new oglBuffer(bd, target, id, vaoID);

	if(bd.data)
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
	glBindVertexArray(vaoID);

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	
	// format data
	// positions(Vec3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
	glEnableVertexAttribArray(0);

	// normals(Vec3)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
	glEnableVertexAttribArray(1);

	// texCoords(Vec2)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texCoord));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	return 0;
}
int oglBufferFactory::createUniformBuffer(BufferDescription& bd, GLuint& id, GLuint binding)
{
	glGenBuffers(1, &id);

	glBindBuffer(GL_UNIFORM_BUFFER, id);

	glBufferData(GL_UNIFORM_BUFFER, bd.size * bd.count, nullptr, GL_STATIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);

	return 0;
}
