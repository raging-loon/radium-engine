#ifndef CORE_EVENT_EVENT_SYSTEM_H_
#define CORE_EVENT_EVENT_SYSTEM_H_

#include "core/types.h"
#include <functional>
namespace radium
{


template <typename Ret, typename... Args>
using EventCallback = std::function<Ret(Args...)>;

struct IEvent
{
	IEvent() : 
		handled(false) {}
	bitbool handled;

};

} // radium


#endif // CORE_EVENT_EVENT_SYSTEM_H_