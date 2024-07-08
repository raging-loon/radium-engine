#ifndef GRAPHICS_UNIFORM_DATA_
#define GRAPHICS_UNIFORM_DATA_

#include "math/math.h"
#include "core/types.h"
namespace radium
{

#ifdef RAD_API_OPENGL

constexpr U32 GLSL_SCENE_DATA_BINDING  = 1;
constexpr U32 GLSL_OBJECT_DATA_BINDING = 2;
constexpr U32 GLSL_LIGHT_DATA_BINDING  = 3;


#endif // RAD_API_OPENGL

struct SceneData
{
	glm::vec3 cameraPosition;
};

struct ObjectData
{
	glm::mat4x4 worldViewProjection;
	glm::mat4x4 model;
	glm::vec4	color;
};


struct LightData
{

};


} // radium

#endif // GRAPHICS_UNIFORM_DATA_