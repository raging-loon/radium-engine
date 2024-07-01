#include "IDisplay.h"

#ifdef RAD_PLATFORM_WIN32
# include "platform/win32/Win32Display.h"
#endif // RAD_PLATFORM_WIN32

using radium::IDisplay;

IDisplay* IDisplay::createDisplay()
{
#ifdef RAD_PLATFORM_WIN32
	return new radium::win32::Win32Display();
#endif // RAD_PLATFORM_WIN32
}