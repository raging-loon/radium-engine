#ifndef CORE_INPUT_H_
#define CORE_INPUT_H_

#include "core/types.h"
#include "math/math.h"

#ifdef RAD_PLATFORM_WIN32
# include "platform/win32/Win32KeyCodes.h"
#endif // RAD_PLATFORM_WIN32

namespace radium
{


using KeyCode = U16;
/* Implementation found in `platform/<platform>/<platform>InputImpl.cpp` */
namespace Input
{

	bool isKeyPressed(KeyCode kc);
	bool isMouseButtonPressed(KeyCode kc);
	
	float getMouseX();
	float getMouseY();
	
	math::Vec2 getMousePosition();

	bool getKeyComboPressed(KeyCode kc1, KeyCode...);
};

} // radium


#endif // CORE_INPUT_H_