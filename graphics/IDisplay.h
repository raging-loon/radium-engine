#ifndef GRAPHICS_IDISPLAY_H_
#define GRAPHICS_IDISPLAY_H_

#include "graphics/RenderDriverConfig.h"

namespace radium
{
/**
 * IDisplay - interface through which
 *			  windows are created
*/
class IDisplay
{
public:

	static IDisplay* createDisplay();

	virtual int create(int w, int h, bool windowed, const char* title) = 0;
	virtual void destroy() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;

	virtual void processEvents() = 0;

	virtual RenderDriverConfig createRenderDriverConfig() = 0;

};

} // radium

#endif // GRAPHICS_IDISPLAY_H_