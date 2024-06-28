#ifndef DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_
#define DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_

#include "graphics/IShaderProgram.h"
#include <core/types.h>
namespace radium
{


class oglShaderProgram : public IShaderProgram
{
	friend class oglRenderDriver;
public:
	oglShaderProgram(ShaderID id) : m_shaderID(id) {}

	U32 createUniformBuffer(U32 count, U32 size, U32 binding = 0) override;
	
	void updateUniformBuffer(U32 id, U32 index, const void* data, U32 dataSize) override;

	void setPerObjectUniformBuffer(U32 id, U32 size) override 
	{
		m_perObjectUB = id; 
		m_perObjectItemSize = size;
	}

	ShaderID m_shaderID;
private:

	U32 m_perObjectUB;
	U32 m_perObjectItemSize;
};

} // radium


#endif // DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_