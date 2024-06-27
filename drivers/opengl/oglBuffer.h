#ifndef DRIVERS_OPENGL_OGL_BUFFER_H_
#define DRIVERS_OPENGL_OGL_BUFFER_H_

#include "graphics/IBuffer.h"

#ifdef RAD_API_OPENGL

#include <GL/glew.h>

namespace radium
{

class oglBuffer : public IBuffer
{
public:

	oglBuffer(GLuint bufID, GLenum target, buffer_t type,  GLuint vaoID = GL_INVALID_VALUE);

public:

	void destroy() override;

	buffer_t getType() override { return m_type; }
	buffer_t getType() const	{ return m_type; }

	/* size = count * sizeof(datum) */
	void copyData(unsigned int size, void* data);

	/* opengl specific bind functions */
	void bind();
	void bindVAO();
	void unbind();
	void unbindVAO();

private:

	buffer_t m_type;
	GLuint m_bufferID;
	/* used if this is vertex buffer */
	GLuint m_vertexArrayObject;

	GLenum m_target;
};

} // radium

#endif // RAD_API_OPENGL

#endif // DRIVERS_OPENGL_OGL_BUFFER_H_