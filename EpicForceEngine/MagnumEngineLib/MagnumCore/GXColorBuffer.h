#ifndef _GXColorBuffer_h_
#define _GXColorBuffer_h_

#include "GXPixelBuffer.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the ColorBuffer of Graphics Device
* @see GXPixelBuffer
*/
class GXColorBuffer : public GXPixelBuffer
{
friend class GXContext;
private:
	GXColorBuffer(const GXColorBuffer &buffer_);
	GXColorBuffer &operator = (const GXColorBuffer &buffer_);
public:
	GXColorBuffer(int width_, int height_, const GXPixelFormat &format_);
};

};

#endif