#ifndef GRAPHICS_RENDER_ITEM_H_
#define GRAPHICS_RENDER_ITEM_H_

#include "graphics/IBuffer.h"
#include "core/types.h"
namespace radium
{

// TODO: This might need to be changed when instancing is supported
struct RenderItem
{
	IBuffer* vertexBuffer;
	IBuffer* indexBuffer;

	U32 uniformIndex;
	
};


} // radium


#endif // GRAPHICS_RENDER_ITEM_H_