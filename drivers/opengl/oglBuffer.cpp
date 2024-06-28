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



oglBuffer::oglBuffer(U32 count, GLuint bufID, GLenum target, buffer_t type, GLuint vaoID)
	: count(count), m_type(type), m_bufferID(bufID), m_vertexArrayObject(vaoID), m_target(target)
{
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

void oglBuffer::copyData(unsigned int size, void* data) 
{
	assert(data != nullptr);
	glBufferData(
		m_target,
		size,
		data,
		// TODO: this might need to be configured later
		GL_STATIC_DRAW
	);
}
