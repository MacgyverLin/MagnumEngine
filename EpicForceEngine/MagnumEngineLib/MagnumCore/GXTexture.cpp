#include "GXTexture.h"
#include "GXContext.h"
#include "PVRTexLoad.h"

GXTexture::GXTexture(const GXPixelBufferType &type_, int width_, int height_, const GXPixelFormat &format_, const GXPixelBufferOption &option_)
: GXPixelBuffer(type_, width_, height_, format_, option_)
, filter(GXTextureMagFilterMode::Linear, GXTextureMinFilterMode::Linear)
, wrap(GXTextureWrapMode::Repeat, GXTextureWrapMode::Repeat)
, maxAnisotropy(1.0f)
{
	// this.state = new TextureState ();
}

GXTexture::GXTexture(const GXPixelBufferType &type_, const char *fileName_)
: GXPixelBuffer()
, filter(GXTextureMagFilterMode::Linear, GXTextureMinFilterMode::Linear)
, wrap(GXTextureWrapMode::Repeat, GXTextureWrapMode::Repeat)
, maxAnisotropy(1.0f)
{
	// int num = PsmTexture.FromFile (type, fileName, mipmap, format, out this.handle);
	// if (num != 0)
	// {
		// Error.ThrowNativeException (num);
	// }
	
	// PsmPixelBuffer.GetInfo (this.handle, out this.type, out this.width, out this.height, out this.level, out this.format, out this.option);
	// this.state = new TextureState ();

	if(!FileIO::exists(fileName_))
		return;

	int length = FileIO::length(fileName_);
	Vector<char> fileImage;
	fileImage.resize(length);

	int len = strlen(fileName_);
	int loadoffset = 0;
	if(tolower(fileName_[len-1])=='r')
		loadoffset=0;
	else
		loadoffset=11*4;

	bool rval = FileIO::load(fileName_, &fileImage[0], length, loadoffset);
	if(rval)
	{
		this->type	 = type_;
		this->option = GXPixelBufferOption::None;

		this->handle = PVRTTextureLoadFromPointer(&fileImage[0], true, 
												  this->width, this->height, this->format, this->levelCount);
	}
}

GXTexture::GXTexture(const GXPixelBufferType &type_, const char *fileImage_, unsigned int length_)
: GXPixelBuffer()
, filter(GXTextureMagFilterMode::Linear, GXTextureMinFilterMode::Linear)
, wrap(GXTextureWrapMode::Repeat, GXTextureWrapMode::Repeat)
, maxAnisotropy(1.0f)
{
	// int num = PsmTexture.FromImage (type, fileImage, mipmap, format, out this.handle);
	// if (num != 0)
	// {
		// Error.ThrowNativeException (num);
	// }
	// PsmPixelBuffer.GetInfo (this.handle, out this.type, out this.width, out this.height, out this.level, out this.format, out this.option);
	// this.state = new TextureState ();

	this->type	 = type_;
	this->option = GXPixelBufferOption::None;

	this->handle = PVRTTextureLoadFromPointer(fileImage_, true, 
											  this->width, this->height, this->format, this->levelCount);
}

GXTexture::~GXTexture()
{
	for(int i=0; i<GXContext::NUM_TEXTURES; i++)
	{
		const GXTexture *texture = GXContext::instance().getTexture(i);
		if(texture==this)
		{
			GXContext::instance().setTexture(i, 0);
		}
	}

	if(this->handle)
	{
		glDeleteTextures(1, &this->handle);
		handle = 0;
	}
}

const GXTextureFilterState &GXTexture::getFilter() const
{
	return this->filter;
}

void GXTexture::setFilter(const GXTextureFilterState &filter_)
{
	this->filter = filter_;
}

void GXTexture::setFilter(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_)
{
	filter.set(mag_, min_);
}

const GXTextureWrapState &GXTexture::getWrap() const
{
	return this->wrap;
}

void GXTexture::setWrap(const GXTextureWrapState &wrap_)
{
	this->wrap = wrap_;
}

void GXTexture::setWrap(const GXTextureWrapMode &mode_)
{
	wrap.set(mode_, mode_);
}

void GXTexture::setWrap(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_)
{
	wrap.set(wrapS_, wrapT_);
}

float GXTexture::getMaxAnisotropy() const
{
	return maxAnisotropy;
}

void GXTexture::setMaxAnisotropy(float maxAnisotropy_)
{
	maxAnisotropy = maxAnisotropy_;
}