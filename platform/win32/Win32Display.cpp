#include "Win32Display.h"
#include "core/debug/Log.h"

#include <Windows.h>
#ifdef RAD_API_OPENGL
# include <GL/glew.h>
# include <GL/wglext.h>
# include <wingdi.h>
#endif // RAD_API_OPENGL

using radium::win32::Win32Display;

LRESULT Win32Display::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Tie event system here
	return DefWindowProc(hWnd, message, wParam, lParam);
}


Win32Display::Win32Display()
	: m_hInstance(nullptr), m_hwnd(nullptr)
{
	memset(&m_winfo, 0, sizeof(WNDCLASSEX));
}

int Win32Display::create(int w, int h, bool windowed, const char* title)
{
	m_hInstance = (HINSTANCE)GetModuleHandle(NULL);

	m_winfo =
	{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WndProc,
		.hInstance = m_hInstance,
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.hbrBackground = (HBRUSH)COLOR_WINDOW,
		.lpszClassName = "Win32Window"
	};

	if (!RegisterClassEx(&m_winfo))
	{
		RAD_ENGINE_CRITICAL("[Win32Display] Failed to register window class");
		return -1;
	}

	m_hwnd = CreateWindowExA(
		NULL,
		"Win32Window",
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		w, h,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	if (!m_hwnd)
	{
		RAD_ENGINE_CRITICAL("Failed to create window");
		return -1;
	}

	return 0;
}


void Win32Display::destroy()
{
	if (m_hwnd)
		DestroyWindow(m_hwnd);
#ifdef RAD_API_OPENGL
	if (m_glCtx)
		wglDeleteContext(m_glCtx);
#endif // RAD_API_OPENGL
}

void Win32Display::show()
{
	assert(m_hwnd);
	ShowWindow(m_hwnd, SW_SHOW);
}


void Win32Display::hide()
{
	assert(m_hwnd);
	ShowWindow(m_hwnd, SW_HIDE);


}

#ifdef RAD_API_OPENGL

int Win32Display::createGLContext()
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
	

	HDC handleToDevCtx = GetDC(m_hwnd);

	int pixelFormat = ChoosePixelFormat(handleToDevCtx, &pfd);
	SetPixelFormat(handleToDevCtx, pixelFormat, &pfd);

	m_glCtx = wglCreateContext(handleToDevCtx);
	

	if (!m_glCtx)
	{
		RAD_ENGINE_CRITICAL("Win32Display: Failed to create OpenGL Context");
		return -1;
	}
	
	wglMakeCurrent(handleToDevCtx, m_glCtx);

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
		RAD_ENGINE_CRITICAL("[Win32] Failed to load wglCreateContextAttribsARB");
		abort();
	}
	// make a debug context
	auto debugCtx = wglCreateContextAttribsARB(handleToDevCtx, 0, debugAttribs);

	// delete current context
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(m_glCtx);
	wglMakeCurrent(handleToDevCtx, debugCtx);

	m_glCtx = debugCtx;
	if (!m_glCtx)
	{
		RAD_ENGINE_CRITICAL("Win32Display: Failed to create OpenGL Debug Context");
		return -1;
	}
	RAD_ENGINE_INFO("[Win32Display]: Created OpenGL Debug Context: {}", (char*)(glGetString(GL_VERSION)));

#else
	RAD_ENGINE_INFO("[Win32] Created OpenGL context: {}", (char*)(glGetString(GL_VERSION)));
#endif // RAD_DEBUG

	


	return 0;
}


void Win32Display::processEvents()
{
	MSG msg;
	while (PeekMessage(&msg, m_hwnd, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


#endif // RAD_API_OPENGL