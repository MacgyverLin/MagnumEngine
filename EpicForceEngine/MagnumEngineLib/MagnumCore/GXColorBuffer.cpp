#include "GXColorBuffer.h"

GXColorBuffer::GXColorBuffer(int width_, int height_, const GXPixelFormat &format_) 
: GXPixelBuffer(GXPixelBufferType::GXColorBuffer, width_, height_, format_, GXPixelBufferOption::None)
{
}