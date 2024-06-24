#ifndef DRIVERS_OPENGL_GL_RENDER_DRIVER_H_
#define DRIVERS_OPENGL_GL_RENDER_DRIVER_H_

#include "graphics/IRenderDriver.h"

namespace radium
{

class glRenderDriver : public IRenderDriver
{
public:
	glRenderDriver();
	~glRenderDriver();
	
	int init() override;
	void terminate() override;

	glRenderDriver(const glRenderDriver&) = delete;
	glRenderDriver& operator=(const glRenderDriver&) = delete;

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
		
};


}


#endif // DRIVERS_OPENGL_GL_RENDER_DRIVER_H_