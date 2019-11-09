#ifndef _GXPrimitive_h_
#define _GXPrimitive_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXPrimitive encapsulate a Primitive of Graphics Device
*/
class GXPrimitive
{
friend class GXContext;
public:
	GXPrimitive(const GXDrawMode &mode_, int first_, int count_, int userData_);
	
	void set(const GXDrawMode &mode_, int first_, int count_, int userData_);
private:
	GXDrawMode		mode;
	unsigned short	first;
	unsigned short	count;
	unsigned short	userData;
};

};

#endif