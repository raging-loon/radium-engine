#include "Win32Display.h"
#include "core/debug/Log.h"

#include <Windows.h>
#ifdef RAD_API_OPENGL
# include <GL/GL.h>
#include <wingdi.h>
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

	RAD_ENGINE_INFO("[Win32] Created OpenGL context: {}", (char*)(glGetString(GL_VERSION)));


	return 0;
}

#endif // RAD_API_OPENGL