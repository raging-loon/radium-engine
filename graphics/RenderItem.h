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
	math::Mat4x4 worldViewProj;
	math::Vec4 color;
};

struct TestPerPassData
{
	math::Vec3 cameraPosition;
};


} // radium


#endif // GRAPHICS_RENDER_ITEM_H_