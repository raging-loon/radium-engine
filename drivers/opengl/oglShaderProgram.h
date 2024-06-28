#ifndef DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_
#define DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_

#include "graphics/IShaderProgram.h"
#include <core/types.h>
namespace radium
{


class oglShaderProgram : public IShaderProgram
{

public:
	oglShaderProgram(ShaderID id) : m_shaderID(id) {}

	U32 createUniformBuffer(U32 count, U32 size, U32 binding = 0) override;
	
	void updateUniformBuffer(U32 id, U32 index, const void* data, U32 dataSize) override;

	ShaderID m_shaderID;
private:

};

} // radium


#endif // DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_