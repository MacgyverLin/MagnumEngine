#ifndef _GXDepthBuffer_h_
#define _GXDepthBuffer_h_

#include "GXPixelBuffer.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Depth Buffer of Graphics Device
* @see GXPixelBuffer
*/
class GXDepthBuffer : public GXPixelBuffer
{
friend class GXContext;
private:
	GXDepthBuffer(const GXDepthBuffer &buffer_);
	GXDepthBuffer &operator = (const GXDepthBuffer &buffer_);
public:
	GXDepthBuffer(int width_, int height_, const GXPixelFormat &format_);
};

};

#endif