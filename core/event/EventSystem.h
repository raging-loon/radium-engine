#ifndef CORE_EVENT_EVENT_SYSTEM_H_
#define CORE_EVENT_EVENT_SYSTEM_H_

#include "core/function.h"
#include "core/types.h"

namespace radium
{


template <typename Ret, typename... Args>
using EventCallback = radium::function<Ret,Args...>;

struct IEvent
{
	IEvent() : 
		handled(false) {}
	bitbool handled;

};

class EventDispatcher
{
public:

	constexpr explicit EventDispatcher(IEvent& e)
		: m_event(e)
	{

	}
	


private:

	IEvent& m_event;

};





} // radium


#endif // CORE_EVENT_EVENT_SYSTEM_H_