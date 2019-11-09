#include "GXPixelBuffer.h"
#include "GXContext.h"

GXPixelBuffer::GXPixelBuffer(const GXPixelBufferType &type_, 
	                         int width_, int height_, 
	                         const GXPixelFormat &format_, const GXPixelBufferOption &option_)
{
	/*
	int num = PsmGXPixelBuffer.Create (type, width, height, mipmap, format, option, out this->handle);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	PsmGXPixelBuffer.GetInfo (this->handle, out this->type, out this->width, out this->height, out this->level, out this->format, out this->option);
	*/
	this->type			= type_;
	this->width			= width_;
	this->height		= height_;
	this->format		= format_;
	this->option		= option_;

	this->levelCount	= 0;
	this->handle		= 0;
}

GXPixelBuffer::GXPixelBuffer()
{
	this->type			= 0;
	this->width			= 0;
	this->height		= 0;
	this->format		= 0;
	this->option		= 0;

	this->levelCount	= 0;
	this->handle		= 0;
}

GXPixelBuffer::~GXPixelBuffer()
{
	this->type			= 0;
	this->width			= 0;
	this->height		= 0;
	this->format		= 0;
	this->option		= 0;

	this->levelCount	= 0;
	this->handle		= 0;
}

const GXPixelBufferType &GXPixelBuffer::getType() const
{
	return this->type;
}

const GXPixelBufferOption &GXPixelBuffer::getOption() const
{
	return this->option;
}

const GXPixelFormat &GXPixelBuffer::getFormat() const
{
	return this->format;
}

int GXPixelBuffer::getWidth() const
{
	return this->width;
}

int GXPixelBuffer::getHeight() const
{
	return this->height;
}

int GXPixelBuffer::getLevelCount() const
{
	return this->levelCount;
}

unsigned int GXPixelBuffer::getHandle() const
{
	return this->handle;
}

bool GXPixelBuffer::isRenderable() const
{
	return (this->option & GXPixelBufferOption::Renderable) != GXPixelBufferOption::None;
}

bool GXPixelBuffer::isPowerOfTwo() const
{
	return isPowerOfTwo(this->width) && isPowerOfTwo (this->height);
}

int GXPixelBuffer::getMipmapWidth(int level_) const
{
	return getMipmapSize(level_, this->levelCount, this->width);
}

int GXPixelBuffer::getMipmapHeight(int level_) const
{
	return getMipmapSize(level_, this->levelCount, this->height);
}

int GXPixelBuffer::getMipmapSize(int level_, int levelCount_, int baseSize_)
{
	if (level_ < 0 || level_ >= levelCount_)
	{
		return -1;
	}

	int num = baseSize_ >> level_;

	return (num > 0) ? num : ((baseSize_ > 0) ? 1 : 0);
}

bool GXPixelBuffer::isPowerOfTwo(int num)
{
	return num != 0 && (num & num - 1) == 0;
}