/* Implementation of Input functions found in core/input/Input.h */

#include <Windows.h>
#include "math/math.h"
#include "core/input/Input.h"

using radium::math::Vec2;

namespace radium::Input
{

bool isKeyPressed(KeyCode kc)
{
	return (GetKeyState(kc) & 0x8000);
}

bool isMouseButtonPressed(KeyCode kc)
{
	return (GetKeyState(kc) & 0x8000);
}

Vec2 getMousePosition()
{
	POINT p;
	
	GetCursorPos(&p);

	return { (float)p.x, (float)p.y };
}

float getMouseX()
{
	return getMousePosition().x;
}

float getMouseY()
{
	return getMousePosition().y;
}
//bool getKeyComboPressed(KeyCode kc1, KeyCode...)
//{
//
//}

} // radium::Input