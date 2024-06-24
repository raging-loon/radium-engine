#ifndef GRAPHICS_IDISPLAY_H_
#define GRAPHICS_IDISPLAY_H_

namespace radium
{
/**
 * IDisplay - interface through which
 *			  windows are created
 * 
 * In OpenGL builds, the display is 
 * repsonsible for creating the OpenGL context.
 * 
 * With DirectX and Vulkan, each respective API
 * is resposible for creating their own contexts.
 * 
*/
class IDisplay
{
public:

	virtual int create(int w, int h, bool windowed, const char* title) = 0;
	virtual void destroy() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;

#ifdef RAD_API_OPENGL
	virtual int createGLContext() = 0;
#endif // RAD_API_OPENGL

};

} // radium

#endif // GRAPHICS_IDISPLAY_H_