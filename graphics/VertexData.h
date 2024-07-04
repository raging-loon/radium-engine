#ifndef GRAPHICS_VERTEX_DATA_H_
#define GRAPHICS_VERTEX_DATA_H_

#include "math/math.h"
#include "core/types.h"
namespace radium
{


struct VertexData
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

using IndexData = U32;


} // radium

#endif // GRAPHICS_VERTEX_DATA_H_