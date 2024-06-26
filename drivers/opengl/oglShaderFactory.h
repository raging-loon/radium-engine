#ifndef DRIVERS_OPENGL_OGL_SHADER_FACTORY_H_
#define DRIVERS_OPENGL_OGL_SHADER_FACTORY_H_

#ifdef RAD_API_OPENGL

#include <GL/glew.h>
#include "core/types.h"
#include "graphics/IShaderProgram.h"

namespace radium
{

class oglShaderFactory
{
public:
	/* create and link shader program */
	static GLuint createShaderProgram(ShaderProgramDescription& spd);

	/* Create a shader from a shader description and source */
	static GLuint createShader(ShaderDescription& sd, const char* source, U32 size);

private:

	/* Given a buffer, attempt to extract the section marked with `#section <sectionName>` */
	static int _int_extractShader(const char* sectionName, const char* source, U32 sourceSize, char* out, U32 outSize);
	/* Actually create the shader */
	static GLuint _int_createShader(GLenum type, const char* source, U32 size);

	static char* _int_readShader(const char* filename, U32& size);

	static GLuint _int_linkShaderProgram(GLuint shaders[], U8 numShaders);
};

} // radium

#endif // RAD_API_OPENGL

#endif // DRIVERS_OPENGL_OGL_SHADER_FACTORY_H_

