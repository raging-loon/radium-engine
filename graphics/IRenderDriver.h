#ifndef GRAPHICS_IRENDER_DRIVER_H_
#define GRAPHICS_IRENDER_DRIVER_H_

#include "RenderDriverConfig.h"
#include "IShaderProgram.h"
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

/**
 * Interface through which communication with graphics APIs
 * is commenced
*/
class IRenderDriver
{
public:
	virtual int init(RenderDriverConfig& rdc) = 0;
	virtual void terminate() = 0;


	virtual IBuffer* createBuffer(BufferDescription& bd) = 0;
	virtual ShaderID createShader(ShaderProgramDescription& sd) = 0;


	virtual void setClearColor(float r, float g, float b, float a) = 0;
	
	virtual void setViewport(int x, int y, int w, int h) = 0;
	
	virtual void swapBuffers() = 0;
	
	virtual void clear() = 0;

private:


};

} // radium


#endif // GRAPHICS_IRENDER_DRIVER_H_