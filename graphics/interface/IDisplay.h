#ifndef GRAPHICS_IDISPLAY_H_
#define GRAPHICS_IDISPLAY_H_

#include "graphics/component/RenderDriverConfig.h"
#include "core/SmartPtr.h"
#include "core/event/Events.h"
#include "core/event/EventSystem.h"
#include <functional>
namespace radium
{


/**
 * IDisplay - interface through which
 *			  windows are created
*/
class __declspec(novtable) IDisplay
{
public:
	using WindowCloseCallback =  std::function<void(WindowCloseEvent*)>;
	using WindowResizeCallback = std::function<void(WindowResizeEvent*)>;

	static Ref<IDisplay> createDisplay();

	virtual int create(int w, int h, bool windowed, const char* title) = 0;
	virtual void destroy() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;

	virtual void processEvents() = 0;

	virtual RenderDriverConfig createRenderDriverConfig() = 0;

	virtual void setWindowResizeCallback(WindowResizeCallback wrc) = 0;

	virtual void setWindowCloseCallback(WindowCloseCallback wcc) = 0;

private:

};

} // radium

#endif // GRAPHICS_IDISPLAY_H_