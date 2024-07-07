#ifndef GRAPHICS_ISHADER_PROGRAM_H_
#define GRAPHICS_ISHADER_PROGRAM_H_

#include "core/types.h"
#include "math/math.h"
namespace radium
{

struct ShaderDescription;

using ShaderID = U32;



/**
 * IShaderProgram
 * 
 * A collection of individual shader functions
 * compiled and linked together
 * 
 * OpenGL Specific:
 *	- created via oglRenderDriver::createShader(ShaderProgramDescription&)
 *	- this will create a shader using oglShaderFactory
 */
class IShaderProgram
{
public:

	enum Type
	{
		NONE,
		VERTEX,
		PIXEL
	};

	virtual void setInt(const char* name, U32 v) = 0;
	virtual void setFloat(const char* name, float v) = 0;
	
	virtual void setVec3(const char* name, glm::vec3 v) = 0;
	virtual void setVec3(const char* name, float v0, float v1, float v2) = 0;
	
	virtual void setVec4(const char* name, glm::vec4 v) = 0;
	virtual void setVec4(const char* name, float v0, float v1, float v2, float v3) = 0;



};


/* Description of a shader program */
struct ShaderProgramDescription
{

	ShaderDescription* vertexShader;
	ShaderDescription* pixelShader;

	const char* filename{ nullptr };
};

// Description of an invidivual shader file/function
struct ShaderDescription
{
	IShaderProgram::Type type{ IShaderProgram::NONE };

	union
	{
		/* DirectX */
		const char* functionName;
		/* OpenGL */
		const char* sectionName;
	};

};

} // radium

#endif // GRAPHICS_ISHADER_PROGRAM_H_