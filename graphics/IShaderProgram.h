#ifndef GRAPHICS_ISHADER_PROGRAM_H_
#define GRAPHICS_ISHADER_PROGRAM_H_

#include "core/types.h"

namespace radium
{

struct ShaderDescription;

struct ShaderProgramDescription
{

	ShaderDescription* vertexShader;
	ShaderDescription* pixelShader;
	
	const char* filename{ nullptr };
};


class IShaderProgram
{
public:

	enum Type
	{
		NONE,
		VERTEX,
		PIXEL
	};

	virtual bool compileShader(ShaderProgramDescription& sd) = 0;


};

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


using ShaderID = unsigned int;

} // radium

#endif // GRAPHICS_ISHADER_PROGRAM_H_