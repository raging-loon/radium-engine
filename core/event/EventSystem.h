#ifndef CORE_EVENT_EVENT_SYSTEM_H_
#define CORE_EVENT_EVENT_SYSTEM_H_

#include "core/types.h"
#include <functional>



template <class C, class Fn>
constexpr auto bind_event_callback(C* klass, Fn&& cb)
{
	return [klass, cb = std::forward<Fn>(cb)](auto&&... args) -> decltype(auto)
	{
		return (klass->*cb)(std::forward<decltype(args)>(args)...);
	};
}

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