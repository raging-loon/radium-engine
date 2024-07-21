#ifndef CORE_INPUT_H_
#define CORE_INPUT_H_

#include "core/types.h"
#include "math/math.h"

#ifdef RAD_PLATFORM_WIN32
# include "platform/win32/Win32KeyCodes.h"
# include "platform/win32/Win32InputImpl.h"
#endif // RAD_PLATFORM_WIN32

/* Implementation found in `platform/<platform>/<platform>InputImpl.cpp` */


#endif // CORE_INPUT_H_