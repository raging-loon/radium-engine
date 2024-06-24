#ifdef RAD_DEBUG

#include "glRenderDriver.h"
#include "core/debug/Log.h"
#include <GL/glew.h>


/*******************************************************/
/************** GL DEBUG CALLBACK/PARSING **************/
/*******************************************************/

using radium::glRenderDriver;
void glRenderDriver::glErrorCallback(
	unsigned int source,
	unsigned int type,
	unsigned int id,
	unsigned int severity,
	int length,
	const char* message,
	const void* uParam)
{
	const char* sourceStr = debugGetSource(source);
	const char* typeStr = debugGetType(type);

	switch (severity)
	{
		//																	yes I know. Thank C++20
	case GL_DEBUG_SEVERITY_HIGH:            RAD_ENGINE_CRITICAL	("[GL] Source: {}; Type: {}; Message: {}", sourceStr, typeStr, message); return;
	case GL_DEBUG_SEVERITY_MEDIUM:          RAD_ENGINE_ERROR	("[GL] Source: {}; Type: {}; Message: {}", sourceStr, typeStr, message); return;
	case GL_DEBUG_SEVERITY_LOW:             RAD_ENGINE_WARN		("[GL] Source: {}; Type: {}; Message: {}", sourceStr, typeStr, message); return;
	case GL_DEBUG_SEVERITY_NOTIFICATION:    RAD_ENGINE_TRACE	("[GL] Source: {}; Type: {}; Message: {}", sourceStr, typeStr, message); return;
	}
}


const char* glRenderDriver::debugGetSource(unsigned int source)
{
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:               return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     return "WINDOW SYSTEM";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:   return "SHADER COMPILER";
	case GL_DEBUG_SOURCE_THIRD_PARTY:       return "THIRD PARTY";
	case GL_DEBUG_SOURCE_APPLICATION:       return "APPLICATION";
	case GL_DEBUG_SOURCE_OTHER:             return "OTHER";
	}
	return "UNKNOWN";
}

const char* glRenderDriver::debugGetType(unsigned int type)
{
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               return "Error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behavior";
	case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
	case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
	case GL_DEBUG_TYPE_MARKER:              return "Marker";
	case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
	case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
	case GL_DEBUG_TYPE_OTHER:               return "Other";
	}
	return "Unknown";
}

#endif // RAD_DEBUG