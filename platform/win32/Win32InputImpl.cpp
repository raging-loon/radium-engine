/* Implementation of Input functions found in core/input/Input.h */

#include <Windows.h>
#include "math/math.h"
#include "Win32InputImpl.h"
#include "core/debug/Log.h"

namespace radium
{

HWND Input::m_windowHandle = nullptr;

bool Input::init()
{
	HWND wh = GetActiveWindow();
	if (!wh)
	{
		RAD_ENGINE_ERROR("[Win32/Input] No Active window found!");
		return false;
	}

	m_windowHandle = wh;

	return true;
}

bool Input::isKeyPressed(KeyCode kc)
{
	return (GetKeyState(kc) & 0x8000);
}

bool Input::isMouseButtonPressed(KeyCode kc)
{
	return (GetKeyState(kc) & 0x8000);
}

glm::vec2 Input::getMousePosition()
{
	POINT p;
	
	GetCursorPos(&p);
	ScreenToClient(m_windowHandle, &p);
	return { (float)p.x, (float)p.y };
}

void Input::setMousePosition(glm::ivec2 pos)
{
	POINT p = { .x = pos.x, .y = pos.y };

	ClientToScreen(m_windowHandle, &p);
	SetCursorPos(p.x, p.y);
}

float Input::getMouseX()
{
	return getMousePosition().x;
}

float Input::getMouseY()
{
	return getMousePosition().y;
}
//bool getKeyComboPressed(KeyCode kc1, KeyCode...)
//{
//
//}

} // radium::Input