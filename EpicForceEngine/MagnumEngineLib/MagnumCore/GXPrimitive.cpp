#include "GXPrimitive.h"

GXPrimitive::GXPrimitive(const GXDrawMode &mode_, int first_, int count_, int userData_)
{
	set(mode_, first_, count_, userData_);
}
	
void GXPrimitive::set(const GXDrawMode &mode_, int first_, int count_, int userData_)
{
	this->mode		= mode_;
	this->first		= (unsigned short)first_;
	this->count		= (unsigned short)count_;
	this->userData	= (unsigned short)userData_;
}