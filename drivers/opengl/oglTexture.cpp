#include "oglTexture.h"

#include <GL/glew.h>

using radium::oglTexture;

void oglTexture::activate()
{
	glBindTexture(GL_TEXTURE_2D, m_texId);
}