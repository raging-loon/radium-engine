#ifndef GRAPHICS_PASS_CONSTANTS_H_
#define GRAPHICS_PASS_CONSTANTS_H_

#include "math/math.h"

namespace radium
{
/**
 * PassConstants
 * 
 * During each iteration of the game loop, multiple uniform buffers 
 * will need to be uploaded to the GPU.
 * 
 * To minimize traffic, per-frame/per-pass data is stored here.
 * 
 * To initialize the passConstantBuffer, you must call
 *	- RenderDriver::initPassConstantBuffer();
 * To update:
 *  - RenderDriver::updatePassConstantBuffer(PassConstants* data);
 * 
 **/
struct PassConstants
{
	math::Vec3 cameraPosition;
};

} // radium


#endif // GRAPHICS_PASS_CONSTANTS_H_
