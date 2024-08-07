#ifndef PLATFORM_WIN32_DISPLAY_H_
#define PLATFORM_WIN32_DISPLAY_H_

#include <functional>
#include "graphics/interface/IDisplay.h"
#include "graphics/component/RenderDriverConfig.h"
#include "graphics/interface/Adapter.h"
#include <Windows.h>

namespace radium::win32
{

/* Custom Messages posted in WndProc */
/* With this, we can capture messages in the message loop */
constexpr UINT RWM_SIZING = WM_USER + 1;

class Win32Display : public IDisplay
{
public:
	Win32Display();
	~Win32Display() override;
	int create(int w, int h, bool windowed, const char* title) override;
	void destroy() override;

	void show() override;
	void hide() override;
	
	void processEvents() override;
	RenderDriverConfig createRenderDriverConfig() override;

	void setWindowResizeCallback(WindowResizeCallback wrc) { m_resizeCB = wrc;  };

	void setWindowCloseCallback(WindowCloseCallback wcc) { m_closeCB = wcc; };
	void setMouseMoveCallback(MouseMoveCallback mmc) { m_mmvCB = mmc; };
public:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE	m_hInstance;
	HWND		m_hwnd;
	WNDCLASSEX  m_winfo;

	WindowCloseCallback m_closeCB;
	WindowResizeCallback m_resizeCB;
	MouseMoveCallback m_mmvCB;

#ifdef RAD_API_OPENGL
	HGLRC m_glCtx;
#endif // RAD_API_OPENGL
};

} // radium

#endif // PLATFORM_WIN32_DISPLAY_H_

