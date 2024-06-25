#ifndef DRIVERS_OPENGL_OGL_BUFFER_FACTORY_H_
#define DRIVERS_OPENGL_OGL_BUFFER_FACTORY_H_

#include "oglBuffer.h"

namespace radium
{


class oglBufferFactory
{
public:

	oglBuffer* createBuffer(BufferDescription& bd);

private:

	int createIndexBuffer(BufferDescription& bd, GLuint& id);
	int createVertexBuffer(BufferDescription& bd, GLuint& id, GLuint& vaoID);


};

} // radium

#endif // DRIVERS_OPENGL_OGL_BUFFER_FACTORY_H_

