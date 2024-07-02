#include "IDisplay.h"

#ifdef RAD_PLATFORM_WIN32
# include "platform/win32/Win32Display.h"
#endif // RAD_PLATFORM_WIN32

using radium::IDisplay;

radium::Ref<IDisplay> IDisplay::createDisplay()
{
#ifdef RAD_PLATFORM_WIN32
	return radium::MakeRef<radium::win32::Win32Display>();
#endif // RAD_PLATFORM_WIN32
}