#ifndef PLATFORM_WIN32_WIN32_KEY_CODES_H_
#define PLATFORM_WIN32_WIN32_KEY_CODES_H_

#include "core/input/Input.h"
#include <Windows.h>


namespace radium::KeyCodes
{
using KeyCode = U16;

enum : KeyCode
{
	SPACE			= VK_SPACE,
	BACK			= VK_BACK,
	TAB				= VK_TAB,
	CLEAR			= VK_CLEAR,
	ENTER			= VK_RETURN,
	RETURN			= VK_RETURN,
	SHIFT			= VK_SHIFT,
	CONTROL			= VK_CONTROL,
	LMENU			= VK_MENU,
	L_ALT			= VK_MENU,
	PAUSE			= VK_PAUSE, 
	LMB				= VK_LBUTTON,
	RMB				= VK_RBUTTON,
	MMB				= VK_MBUTTON,
	UP				= VK_UP,
	DOWN			= VK_DOWN,
	RIGHT			= VK_RIGHT,
	LEFT			= VK_LEFT,
	ESCAPE			= VK_ESCAPE

};

} // radium


#endif // PLATFORM_WIN32_WIN32_KEY_CODES_H_