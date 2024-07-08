#ifndef DRIVERS_OPENGL_OGL_TEXTURE_H_
#define DRIVERS_OPENGL_OGL_TEXTURE_H_

#include "graphics/interface/ITexture.h"

#include <GL/glew.h>

namespace radium
{

class oglTexture : public ITexture
{
public:
	oglTexture(GLuint id, unsigned int w, unsigned int h)
		: m_texId(id), m_height(h), m_width(w)
	{}

	void activate();

private:
	GLuint m_texId;
	unsigned int m_height;
	unsigned int m_width;

	
};



} // radium

#endif // DRIVERS_OPENGL_OGL_TEXTURE_H_