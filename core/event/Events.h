#ifndef CORE_EVENT_EVENTS_H_
#define CORE_EVENT_EVENTS_H_

/** Built-in events **/
#include "EventSystem.h"
namespace radium
{

struct WindowCloseEvent : public IEvent {};

struct WindowResizeEvent : public IEvent
{
public:

	WindowResizeEvent(int nw, int nh)
		: newWidth(nw), newHeight(nh)
	{
	}

	int newHeight;
	int newWidth;
};

struct MouseMoveEvent : IEvent
{
	MouseMoveEvent(float nx, float ny)
		: x(nx), y(ny)
	{
	}

	float x;
	float y;
};

} // radium

#endif // CORE_EVENT_EVENTS_H_