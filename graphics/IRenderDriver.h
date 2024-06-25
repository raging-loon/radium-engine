#ifndef GRAPHICS_IRENDER_DRIVER_H_
#define GRAPHICS_IRENDER_DRIVER_H_


namespace radium
{

enum class RenderAPI
{
	OPENGL = 1,
	DIRECTX12,
	VULKAN
};

class IBuffer;
struct BufferDescription;

class IRenderDriver
{
public:
	virtual int init() = 0;
	virtual void terminate() = 0;

	virtual IBuffer* createBuffer(BufferDescription& bd) = 0;

private:


};

} // radium


#endif // GRAPHICS_IRENDER_DRIVER_H_