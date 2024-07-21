#ifndef PLATFORM_WIN32_WIN32_INPUT_IMPL_H_
#define PLATFORM_WIN32_WIN32_INPUT_IMPL_H_

#include "core/input/Input.h"
#include "math/math.h"

namespace radium
{

using KeyCode = U16;
/*
	PURPOSE
		A Windows-specific KBM Implementation

		Keyboard Input uses the 'GetKeyState' function

		Mouse Input uses the Handle to the Current window
		to translate mouse coordinates to the current window's
		coordinates.

		Input::init() will find this handle.

*/

class Input
{
public:
	static bool init();

	static bool isKeyPressed(KeyCode kc);
	
	static bool isMouseButtonPressed(KeyCode kc);

	static float getMouseX();
	static float getMouseY();

	/* Returns Mouse Coordinates relative to active window */
	static glm::vec2 getMousePosition();
	/* Sets Mouse Coordinates relative to active window*/
	static void setMousePosition(glm::ivec2 pos);

	// TODO: Add Un-Translated Mouse Coordinates if needed.

	static bool getKeyComboPressed(KeyCode kc1, KeyCode...);

private:
	static HWND m_windowHandle;

};


};

#endif // PLATFORM_WIN32_WIN32_INPUT_IMPL_H_