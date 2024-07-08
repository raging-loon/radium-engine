#ifndef GRAPHICS_RENDER_DRIVER_CONFIG_H_
#define GRAPHICS_RENDER_DRIVER_CONFIG_H_

/**
 * This file contains the RenderDriverConfig structure
 * 
 * This is a platform specific data structure that holds data 
 * needed to initialize various graphics APIs.
 * 
 * The Display Driver (e.g. platform/win32/Win32Display )
 * is responsible for filling this information out and 
 * providing it to whatever subsystem might need it
 * 
*/


#ifdef RAD_PLATFORM_WIN32
#include <Windows.h>

namespace radium
{

struct RenderDriverConfig
{
	HWND		windowHandle{ nullptr };
	HINSTANCE	hinstance	{ nullptr };
#ifdef RAD_API_OPENGL
	HDC			handleDevCtx{ nullptr };
	HGLRC		handleGLCtx	{ nullptr };
#endif // RAD_API_OPENGL
};

} // radium
#else
#error "Unsupproted API!"
#endif // RAD_PLATFORM_WIN32

#endif // GRAPHICS_RENDER_DRIVER_CONFIG_H_