#ifndef DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_
#define DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_

#include "graphics/IShaderProgram.h"
#include <core/types.h>
#include "math/math.h"
#include <GL/glew.h>
#include <unordered_map>

namespace radium
{


class oglShaderProgram : public IShaderProgram
{
	friend class oglRenderDriver;
public:
	oglShaderProgram(ShaderID id) : m_shaderID(id) {}

	bool addParameter(const char* name);

	void setInt(const char* name, U32 v) override;
	void setFloat(const char* name, float v) override;

	void setVec3(const char* name, glm::vec3 v) override;
	void setVec3(const char* name, float v0, float v1, float v2) override;

	void setVec4(const char* name, glm::vec4 v) override;
	void setVec4(const char* name, float v0, float v1, float v2, float v3) override;

	

	ShaderID m_shaderID;
private:

	std::unordered_map<const char*, GLuint> m_uniformMap = {};
}; 

} // radium


#endif // DRIVER_OPENGL_OGL_SHADER_PROGRAM_H_