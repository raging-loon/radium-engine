#if defined(RAD_API_OPENGL) && defined(RAD_PLATFORM_WIN32)

#include "drivers/opengl/oglRenderDriver.h"
#include "core/debug/Log.h"


#include <GL/glew.h>
#include <GL/wglext.h>
#include <wingdi.h>
#include <Windows.h>

int radium::oglRenderDriver::init(RenderDriverConfig& rdc)
{
	PIXELFORMATDESCRIPTOR pfd =
	{

		sizeof(PIXELFORMATDESCRIPTOR),	// nSize
		1,								// nVersion
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // dwFlags
		PFD_TYPE_RGBA,					// iPixelTpype
		32,								// cColorBits
		0, 0, 0, 0, 0, 0,				// RGBA Bits/Shift
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};



	HDC handleToDevCtx = GetDC(rdc.windowHandle);
	
	rdc.handleDevCtx = handleToDevCtx;

	int pixelFormat = ChoosePixelFormat(handleToDevCtx, &pfd);
	SetPixelFormat(handleToDevCtx, pixelFormat, &pfd);

	// used for loading extension
	auto tempCtx = wglCreateContext(handleToDevCtx);


	if (!tempCtx)
	{
		RAD_ENGINE_CRITICAL("[WGL]: Failed to create OpenGL Context");
		return -1;
	}

	wglMakeCurrent(handleToDevCtx, tempCtx);

#ifdef RAD_DEBUG
	/*
	 * To create a OpenGL debug context on windows
	 *	- make a 'non-debug' context
	 *  - use the 'non-debug' context
	 *  - load the extension using the 'non-debug' context
	 *  - create the debug context
	 *  - delete the 'non-debug' context
	 *  - make the current context the debug context
	 *
	*/

	int debugAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		0
	};

	// load extension
	auto* wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (!wglCreateContextAttribsARB)
	{
		RAD_ENGINE_CRITICAL("[WGL]: Failed to load wglCreateContextAttribsARB");
		abort();
	}
	// make a debug context
	rdc.handleGLCtx = wglCreateContextAttribsARB(handleToDevCtx, 0, debugAttribs);

	// delete current context
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(tempCtx);
	wglMakeCurrent(handleToDevCtx, rdc.handleGLCtx);


	if (!rdc.handleGLCtx)
	{
		RAD_ENGINE_CRITICAL("[WGL]: Failed to create OpenGL Debug Context");
		return -1;
	}
	RAD_ENGINE_INFO("[WGL]: Created OpenGL Debug Context: {}", (char*)(glGetString(GL_VERSION)));

#else
	rdc.handleGLCtx = tempCtx;
	RAD_ENGINE_INFO("[WGL]: Created OpenGL context: {}", (char*)(glGetString(GL_VERSION)));
#endif // RAD_DEBUG
	
	
	m_rdc = rdc;

	return _int_init();
} // radium::oglRenderDriver::init

void radium::oglRenderDriver::terminate()
{
	// get rid of current context
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(m_rdc.handleGLCtx);

	// delete device context

	ReleaseDC(m_rdc.windowHandle, m_rdc.handleDevCtx);



	_int_terminate();
}


/*
void radium::oglRenderDriver::swapBuffers()
{
	SwapBuffers(m_rdc.handleDevCtx);
}


*/

#else
#error "Fix SConstruct. This file shouldn't have been added"
#endif // RAD_API_OPENGL && RAD_PLATFORM_WIN32