#ifndef DRIVERS_OPENGL_OGL_BUFFER_H_
#define DRIVERS_OPENGL_OGL_BUFFER_H_

#include "graphics/IBuffer.h"

#ifdef RAD_API_OPENGL

#include <GL/glew.h>

namespace radium
{

class oglBuffer : public IBuffer
{
	friend class oglRenderDriver;
public:

	oglBuffer(BufferDescription& bd, GLenum target, GLuint bufferID, GLuint m_VAO = GL_INVALID_VALUE);

public:

	void destroy() override;

	buffer_t getType() override { return m_type; }
	buffer_t getType() const	{ return m_type; }

	/* size = count * sizeof(datum) */
	void copyData(unsigned int size, void* data) override;
	void copySubData(unsigned int size, void* data, unsigned int offset = 0) override;


	/* Bind m_bufferID */
	void bind();
	/* Bind m_vertexArrayObject */
	void bindVAO();

	void unbind();
	void unbindVAO();

	/* Bind m_bufferID at m_uboBining */
	void bindRange(U32 index);
private:

	U32 m_count;
	U32 m_size;
	buffer_t m_type;
	
	GLenum m_target;
	
	GLuint m_bufferID;

	union
	{
		GLuint m_vertexArrayObject;
		GLuint m_uboBinding;
	};

};

} // radium

#endif // RAD_API_OPENGL

#endif // DRIVERS_OPENGL_OGL_BUFFER_H_