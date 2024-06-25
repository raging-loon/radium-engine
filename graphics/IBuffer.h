#ifndef GRAPHICS_IBUFFER_H_
#define GRAPHICS_IBUFFER_H_

#include "core/types.h"

namespace radium
{

enum class buffer_t
{
	NONE,
	TYPELESS,
	VERTEX,
	INDEX,
	CONSTANT,
	UNIFORM = CONSTANT

};

struct BufferDescription
{
	buffer_t type	= buffer_t::NONE;
	/* size of one(1) element */
	size_t size		= 0;
	/* number of elements */
	size_t count	= 0;
	byte* data		= nullptr;
};



/**
 * Abstract class representing any random buffer
 * any random graphics API can create
*/
class IBuffer
{
public:

	virtual void destroy() = 0;
	virtual buffer_t getType() = 0;
	
};

} // radium

#endif // GRAPHICS_IBUFFER_H_