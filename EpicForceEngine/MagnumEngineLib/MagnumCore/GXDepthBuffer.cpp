#include "GXDepthBuffer.h"

GXDepthBuffer::GXDepthBuffer(int width_, int height_, const GXPixelFormat &format_) 
: GXPixelBuffer(GXPixelBufferType::DepthBuffer, width_, height_, format_, GXPixelBufferOption::None)
{
}