#include "oglBuffer.h"
#include "graphics/IBuffer.h"
#include "core/types.h"
#include "core/debug/Log.h"

#include <GL/glew.h>
#include <cassert>
using radium::oglBuffer;
using radium::BufferDescription;
using radium::buffer_t;
using radium::byte;


oglBuffer::oglBuffer(BufferDescription& bd, GLenum target, GLuint bufferID, GLuint m_VAO)
	: m_count(bd.count), m_size(bd.size), m_type(bd.type), 
	  m_target(target), m_bufferID(bufferID)
{
	// This is a vertex buffer
	if (m_VAO != GL_INVALID_VALUE)
		m_vertexArrayObject = m_VAO;
	else 
		// this is a uniform buffer or this value won't be used 
		m_uboBinding = bd.binding;

}

void oglBuffer::destroy()
{
	if (m_vertexArrayObject != GL_INVALID_VALUE)
		glDeleteVertexArrays(1, &m_vertexArrayObject);

	glDeleteBuffers(1, &m_bufferID);
}

void oglBuffer::bind()
{
	glBindBuffer(m_target, m_bufferID);
}

void oglBuffer::unbind()
{
	glBindBuffer(m_target, 0);
}
void oglBuffer::bindVAO()
{
	glBindVertexArray(m_vertexArrayObject);
}

void oglBuffer::unbindVAO()
{
	glBindVertexArray(0);

}

void oglBuffer::bindRange(U32 index)
{
	
	assert(m_target == GL_UNIFORM_BUFFER ||
		   m_target == GL_SHADER_STORAGE_BUFFER ||
		   m_target == GL_ATOMIC_COUNTER_BUFFER ||
		   m_target == GL_TRANSFORM_FEEDBACK_BUFFER);

	glBindBufferRange(
		m_target,
		m_uboBinding,
		m_bufferID,
		index * m_size,
		m_size
	);
}

void oglBuffer::copyData(unsigned int size, void* data) 
{
	assert(data != nullptr);
	RAD_ENGINE_INFO("INfo here");
	glBufferData(
		m_target,
		size,
		data,
		// TODO: this might need to be configured later
		GL_STATIC_DRAW
	);
}

void oglBuffer::copySubData(unsigned int size, void* data, unsigned int offset)
{
	assert(data != nullptr);
	bind();
	glBufferSubData(
		m_target,
		offset,
		size,
		data
	);

}
