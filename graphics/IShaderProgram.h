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
	/**
	 * createUniformBuffer
	 * 
	 * Creates a constant/uniform buffer for use by shaders
	 * 
	 * @params	- count = number of buffers to generate 
	 *			- size	= sizeof a single buffer
	 *			- binding = OpenGL specific = bind number
	 * 
	 * Returns  - (OpenGL) Buffer ID
	 *			- (DirectX) Buffer Index (to array of `ID3D12Resource`s
	*/
	virtual U32 createUniformBuffer(U32 count, U32 size, U32 binding = 0) = 0;

	/**
	 * updateUniformBuffer
	 * 
	 * Updates uniform buffer with ID `id` (OpenGL) or at index `id` (DirectX12)
	 * 
	 * @param	- id
	 *			- index - index to specific buffer
	 *			- data  - Data to copy. Must be non-null
	 *			- dataSize - sizeof whatever data you are copying
	*/
	virtual void updateUniformBuffer(U32 id, U32 index, const void* data, U32 dataSize) = 0;
	
	//virtual void setPerPassUniformBuffer(U32 id);
	virtual void setPerObjectUniformBuffer(U32 id, U32 size) = 0;
	virtual void setPerPassUniformBuffer(U32 id, U32 size) = 0;

	virtual void setInt(const char* name, U32 v) = 0;
	virtual void setFloat(const char* name, float v) = 0;
	
	virtual void setVec3(const char* name, math::Vec3 v) = 0;
	virtual void setVec3(const char* name, float v0, float v1, float v2) = 0;
	
	virtual void setVec4(const char* name, math::Vec4 v) = 0;
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