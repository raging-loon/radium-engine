#ifndef PLATFORM_WIN32_DISPLAY_H_
#define PLATFORM_WIN32_DISPLAY_H_

#include "graphics/IDisplay.h"
#include "graphics/RenderDriverConfig.h"
#include <Windows.h>

namespace radium::win32
{

class Win32Display : public IDisplay
{
public:
	Win32Display();

	int create(int w, int h, bool windowed, const char* title) override;
	void destroy() override;

	void show() override;
	void hide() override;
	
	void processEvents() override;
	RenderDriverConfig createRenderDriverConfig() override;

public:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE	m_hInstance;
	HWND		m_hwnd;
	WNDCLASSEX  m_winfo;


#ifdef RAD_API_OPENGL
	HGLRC m_glCtx;
#endif // RAD_API_OPENGL
};

} // radium

#endif // PLATFORM_WIN32_DISPLAY_H_

