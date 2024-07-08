#ifndef GRAPHICS_RENDER_ITEM_H_
#define GRAPHICS_RENDER_ITEM_H_

#include "core/types.h"
#include "math/math.h"
#include "scene/resource/Mesh.h"

namespace radium
{

// TODO: This might need to be changed when instancing is supported
struct RenderItem
{
	Mesh* mesh;
	U32 uniformIndex;
	
};

} // radium


#endif // GRAPHICS_RENDER_ITEM_H_