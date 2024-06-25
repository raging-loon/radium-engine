#include "Win32Display.h"
#include "core/debug/Log.h"

#include <Windows.h>

#ifdef RAD_API_OPENGL
# include <GL/glew.h>
# include <GL/wglext.h>
# include <wingdi.h>
#endif // RAD_API_OPENGL

using radium::win32::Win32Display;
using radium::RenderDriverConfig;

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


void Win32Display::processEvents()
{
	MSG msg;
	while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


RenderDriverConfig Win32Display::createRenderDriverConfig()
{
	return { m_hwnd, m_hInstance};
}
