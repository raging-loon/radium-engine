#ifndef GRAPHICS_RENDER_ITEM_H_
#define GRAPHICS_RENDER_ITEM_H_

#include "graphics/IBuffer.h"
#include "core/types.h"
#include "math/math.h"
namespace radium
{

// TODO: This might need to be changed when instancing is supported
struct RenderItem
{
	IBuffer* vertexBuffer;
	IBuffer* indexBuffer;

	U32 uniformIndex;
	
};

struct TestPerObjectData
{
	glm::mat4x4 worldViewProj;
	glm::vec4 color;
};

struct TestPerPassData
{
	glm::vec3 cameraPosition;
};


} // radium


#endif // GRAPHICS_RENDER_ITEM_H_