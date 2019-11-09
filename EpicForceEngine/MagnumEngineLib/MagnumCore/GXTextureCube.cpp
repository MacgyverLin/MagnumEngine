#include "GXTextureCube.h"

GXTextureCube::GXTextureCube(int width_, const GXPixelFormat &format_, const GXPixelBufferOption &option_) 
: GXTexture(GXPixelBufferType::GXTextureCube, width_, width_, format_, option_)
{
}

GXTextureCube::GXTextureCube(const char *fileName_) 
: GXTexture(GXPixelBufferType::GXTextureCube, fileName_)
{
}

GXTextureCube::GXTextureCube(const char *fileImage_, unsigned int length_) 
: GXTexture(GXPixelBufferType::GXTextureCube, fileImage_, length_)
{
}

GXTextureCube::~GXTextureCube()
{
}

void GXTextureCube::setPixels(int level_, const GXTextureCubeFace &cubeFace_, 
	                          const Vector<unsigned char> &pixels_)
{
}

void GXTextureCube::setPixels(int level_, const GXTextureCubeFace &cubeFace_, 
	                          const Vector<unsigned char> &pixels_,
							  int dx_, int dy_, int dw_, int dh_)
{
	setPixels(level_, cubeFace_, pixels_, 
		      GXPixelFormat::None, 
			  0, 0, 
			  dx_, dy_, dw_, dh_);
}

void GXTextureCube::setPixels(int level_, const GXTextureCubeFace &cubeFace_, 
	                          const Vector<unsigned char> &pixels_, 
							  int offset_, int pitch_)
{
	int mipmapWidth		= GXTexture::getMipmapWidth(level_);
	int mipmapHeight	= GXTexture::getMipmapHeight(level_);
	
	setPixels(level_, cubeFace_, pixels_, 
		      GXPixelFormat::None, 
			  offset_, pitch_, 
		      0, 0, mipmapWidth, mipmapHeight);
}

void GXTextureCube::setPixels(int level_, const GXTextureCubeFace &cubeFace_, 
	                          const Vector<unsigned char> &pixels_, const GXPixelFormat &format_)
{
	int mipmapWidth		= GXTexture::getMipmapWidth(level_);
	int mipmapHeight	= GXTexture::getMipmapHeight(level_);

	setPixels(level_, cubeFace_, pixels_, 
		      format, 
			  0, 0,
			  0, 0, mipmapWidth, mipmapHeight);
}
	
void GXTextureCube::setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_, 
							  const GXPixelFormat &format_, 
							  int offset_, int pitch_, 
							  int dx_, int dy_, int dw_, int dh_)
{
}

void GXTextureCube::generateMipmap()
{
}