#include "oglShaderProgram.h"
#include <core/types.h>

#include <GL/glew.h>


using radium::oglShaderProgram;
using radium::U32;

U32 oglShaderProgram::createUniformBuffer(U32 count, U32 size, U32 binding)
{

	U32 ubo;

	glGenBuffers(1, &ubo);
	
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);

	glBufferData(GL_UNIFORM_BUFFER, count * size, nullptr, GL_STATIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER, binding, ubo);

	glBindBufferRange(GL_UNIFORM_BUFFER, binding, ubo, 0, size);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);



	return ubo;
}

void oglShaderProgram::updateUniformBuffer(U32 id, U32 index, const void* data, U32 dataSize)
{
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferSubData(GL_UNIFORM_BUFFER, index * dataSize, dataSize, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}