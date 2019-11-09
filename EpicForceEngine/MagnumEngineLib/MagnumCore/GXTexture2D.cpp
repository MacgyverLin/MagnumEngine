#include "GXTexture2D.h"

GXTexture2D::GXTexture2D(int width_, int height_, const GXPixelFormat &format_, const GXPixelBufferOption &option_)
: GXTexture(GXPixelBufferType::GXTexture2D, width_, height_, format_, option_)
{
}

GXTexture2D::GXTexture2D(const char *fileName_)
: GXTexture(GXPixelBufferType::GXTexture2D, fileName_)
{
}

GXTexture2D::GXTexture2D(const char *fileImage_, unsigned int length_) 
: GXTexture(GXPixelBufferType::GXTexture2D, fileImage_, length_)
{
}

GXTexture2D::~GXTexture2D()
{
}

void GXTexture2D::setPixels(int level_, const Vector<unsigned char> &pixels_)
{
}

void GXTexture2D::setPixels(int level_, 
	                        const Vector<unsigned char> &pixels_, 
							int dx_, int dy_, int dw_, int dh_)
{
	setPixels(level_, pixels_, 
		      GXPixelFormat::None, 
			  0, 0, 
			  dx_, dy_, dw_, dh_);
}

void GXTexture2D::setPixels(int level_,
	                        const Vector<unsigned char> &pixels_, 
							int offset_, int pitch_)
{
	int mipmapWidth		= GXTexture::getMipmapWidth(level_);
	int mipmapHeight	= GXTexture::getMipmapHeight(level_);
	
	setPixels(level_, pixels_, 
		      GXPixelFormat::None, 
			  offset_, pitch_, 
			  0, 0, mipmapWidth, mipmapHeight);
}

void GXTexture2D::setPixels(int level_, 
	                        const Vector<unsigned char> &pixels_, const GXPixelFormat &format_)
{
	int mipmapWidth		= GXTexture::getMipmapWidth(level_);
	int mipmapHeight	= GXTexture::getMipmapHeight(level_);

	setPixels(level_, pixels_,
		      format, 0, 0, 
			  0, 0, mipmapWidth, mipmapHeight);
}

void GXTexture2D::setPixels(int level_, 
	                        const Vector<unsigned char> &pixels_, const GXPixelFormat &format_,
	                        int offset_, int pitch_, 
							int dx_, int dy_, int dw_, int dh_)
{
}

void GXTexture2D::generateMipmap()
{
}