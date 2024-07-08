#include "oglShaderProgram.h"
#include <core/types.h>
#include "core/debug/Log.h"
#include <GL/glew.h>

using radium::oglShaderProgram;
using radium::U32;

bool oglShaderProgram::addParameter(const char* name)
{
	GLuint location = glGetUniformLocation(m_shaderID, name);

	if (location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION)
	{
		RAD_ENGINE_ERROR("[GL] Failed to get uniform '{}' in shader 0x{:X}.", name, m_shaderID);
		
		return false;
	}

	m_uniformMap[name] = location;
	return true;
}

void oglShaderProgram::setInt(const char* name, U32 v)
{
	//assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform1i(m_uniformMap[name], v);
}

void oglShaderProgram::setFloat(const char* name, float v)
{
	assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform1f(m_uniformMap[name], v);

}

void oglShaderProgram::setVec3(const char* name, glm::vec3 v)
{
	assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform3f(m_uniformMap[name], v.x, v.y, v.z);

}

void oglShaderProgram::setVec3(const char* name, float v0, float v1, float v2)
{
	assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform3f(m_uniformMap[name], v0, v1, v2);

}

void oglShaderProgram::setVec4(const char* name, glm::vec4 v)
{
	assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform4f(m_uniformMap[name], v.x, v.y, v.z, v.w);

}

void oglShaderProgram::setVec4(const char* name, float v0, float v1, float v2, float v3)
{
	assert(m_uniformMap.find(name) != m_uniformMap.end());
	glUniform4f(m_uniformMap[name], v0, v1, v2, v3);

}
