#ifndef GRAPHICS_UNIFORM_DATA_
#define GRAPHICS_UNIFORM_DATA_

#include "math/math.h"
#include "core/types.h"
namespace radium
{

#ifdef RAD_API_OPENGL
constexpr U32 GLSL_SCENE_DATA_BINDING = 1;
constexpr U32 GLSL_OBJECT_DATA_BINDING = 2;

#endif // RAD_API_OPENGL

struct SceneData
{
	math::Vec3 cameraPosition;
};

struct ObjectData
{
	math::Mat4x4 worldViewProjection;
	math::Vec4	color;
};





} // radium

#endif // GRAPHICS_UNIFORM_DATA_