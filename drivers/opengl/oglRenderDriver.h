#ifndef DRIVERS_OPENGL_GL_RENDER_DRIVER_H_
#define DRIVERS_OPENGL_GL_RENDER_DRIVER_H_

#include "graphics/IRenderDriver.h"
#include "graphics/IBuffer.h"
#include "graphics/IShaderProgram.h"
#include "drivers/opengl/oglBuffer.h"
#include "drivers/opengl/oglBufferFactory.h"

#include "graphics/RenderItem.h"

namespace radium
{



class oglRenderDriver : public IRenderDriver
{
public:
	oglRenderDriver();
	~oglRenderDriver();
	
	/**
	 *				OpenGL - Platform Specific Implementations
	 * ┌────────────────────────────────────────────────────────────────────┐
	 * ├───────────────────────── Initialization ───────────────────────────┤
	 * │ init is defined in platform/<platform>/gl/glContext.cpp			│
	 * │ _int_init2 is defined here.										│
	 * │																	│
	 * │ init takes care of platform specific initialization, e.g. w/ wgl	│
	 * │																	│
	 * │ _int_init2 takes care of platform independent initialization -		│
	 * │ i.e glewInit, debug layer, glEnable(GL_something)					│
	 * │																	│
	 * │ init calls _int_init2												│
	 * │																	│
	 * ├─────────────────────────── Termination ────────────────────────────┤
	 * │																	│
	 * │ `terminate` is defined in platform/<platform>/gl/glContext.cpp		│
	 * │ `terminate` calls _int_terminate									│
	 * │																	│
	 * ├──────────────────────────── SwapBuffers ───────────────────────────┤
	 * │																	│
	 * │ `swapBuffers` is defined in platform/<platform>/gl/glContext.cpp	│
	 * │																	│
	 * └────────────────────────────────────────────────────────────────────┘
	 * 
	 */
	int init(RenderDriverConfig& rdc) override;
	void terminate() override;
	void swapBuffers() override;

	// end of platform specific functions

	IBuffer* createBuffer(BufferDescription& bd) override;
	IShaderProgram* createShader(ShaderProgramDescription& spd) override;

	void draw(IShaderProgram* shader, RenderItem* drawList, U32 dlSize);

	void setClearColor(float r, float g, float b, float a) override;
	void setViewport(int x, int y, int w, int h) override;
	void clear() override;

	void initPassConstantBuffer() override;
	void updatePassConstantBuffer(PassConstants* p) override;


public:

	oglRenderDriver(const oglRenderDriver&) = delete;
	oglRenderDriver& operator=(const oglRenderDriver&) = delete;

private:

	/* platform agnostic initialization */
	int _int_init();

	/* platform agnostic termination */
	void _int_terminate();

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
		
	/* ShaderProgram ID => ShaderProgram */
	//std::unordered_map<U32, IShaderProgram*> m_spID2spMap;

	IShaderProgram* opaqueShader;

	// TODO: get rid of this and make all oglBufferFactory's functions static
	oglBufferFactory m_bufferFactory;

	RenderDriverConfig m_rdc;

	/* Per-Pass/Per-Frame buffer for GPU traffic minimization */
	oglBuffer* m_perPassConstantBuffer;
};


}


#endif // DRIVERS_OPENGL_GL_RENDER_DRIVER_H_