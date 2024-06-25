#ifndef DRIVERS_OPENGL_GL_RENDER_DRIVER_H_
#define DRIVERS_OPENGL_GL_RENDER_DRIVER_H_

#include "graphics/IRenderDriver.h"
#include "graphics/IBuffer.h"
#include "drivers/opengl/oglBuffer.h"
#include "drivers/opengl/oglBufferFactory.h"

namespace radium
{

class oglRenderDriver : public IRenderDriver
{
public:
	oglRenderDriver();
	~oglRenderDriver();
	
	int init() override;
	void terminate() override;

	oglRenderDriver(const oglRenderDriver&) = delete;
	oglRenderDriver& operator=(const oglRenderDriver&) = delete;

	IBuffer* createBuffer(BufferDescription& bd) override;

private:

#ifdef RAD_DEBUG
	static void glErrorCallback(unsigned int source,
		unsigned int type,
		unsigned int id,
		unsigned int severity,
		int length,
		const char* message,
		const void* uParam);

	static const char* debugGetSource(unsigned int source);
	static const char* debugGetType(unsigned int type);
#endif // RAD_DEBUG
		

	oglBufferFactory m_bufferFactory;
};


}


#endif // DRIVERS_OPENGL_GL_RENDER_DRIVER_H_