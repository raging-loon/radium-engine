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
	switch (message)
	{
	case WM_SIZE:
		PostMessage(hWnd, RWM_SIZING, wParam, lParam);
		return 0;
	//
	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
			SetCursor(NULL);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}


Win32Display::Win32Display()
	: m_hInstance(nullptr), m_hwnd(nullptr), m_closeCB(nullptr), m_resizeCB(nullptr)
{
	memset(&m_winfo, 0, sizeof(WNDCLASSEX));
}

Win32Display::~Win32Display()
{
	destroy();
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
	UpdateWindow(m_hwnd);
	ClipCursor(NULL);

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
	UpdateWindow(m_hwnd);
}


void Win32Display::hide()
{
	assert(m_hwnd);
	ShowWindow(m_hwnd, SW_HIDE);


}

// https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
void Win32Display::processEvents()
{
	MSG msg;
	while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
	{
		// todo: move this into another function
		switch (msg.message)
		{
			
			// Window Resize
			case RWM_SIZING:
			{
				if(m_resizeCB)
				{
					auto nw = LOWORD(msg.lParam);
					auto nh = HIWORD(msg.lParam);
					m_resizeCB(new WindowResizeEvent(nw, nh));
				}
				break;
			}

			case WM_MOUSEMOVE:
			{
				if (m_mmvCB)
				{
					MouseMoveEvent m(LOWORD(msg.lParam), HIWORD(msg.lParam));
					m_mmvCB(&m);
				}
				break;
			}

			default:

				TranslateMessage(&msg);
				DispatchMessage(&msg);
		}


		
	}
}


RenderDriverConfig Win32Display::createRenderDriverConfig()
{
	return { m_hwnd, m_hInstance};
}
