#ifndef GRAPHICS_IRENDER_DRIVER_H_
#define GRAPHICS_IRENDER_DRIVER_H_

#include "RenderDriverConfig.h"

namespace radium
{
class IBuffer;
struct BufferDescription;

enum class RenderAPI
{
	OPENGL = 1,
	DIRECTX12,
	VULKAN
};


class IRenderDriver
{
public:
	virtual int init(RenderDriverConfig& rdc) = 0;
	virtual void terminate() = 0;

	virtual IBuffer* createBuffer(BufferDescription& bd) = 0;

private:


};

} // radium


#endif // GRAPHICS_IRENDER_DRIVER_H_