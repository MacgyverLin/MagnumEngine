#include "GXFrameBuffer.h"
#include "GXContext.h"

GXFrameBuffer::GXFrameBuffer()
{
	this->handle			= 0;
	this->status			= true;
	this->rect.x			= 0;
	this->rect.y			= 0;
	this->rect.width		= 640;
	this->rect.height		= 480;
	this->colorFormat		= 0;
	this->depthFormat		= 0;
	this->multiSampleMode	= 0;
}

GXFrameBuffer::GXFrameBuffer(int width_, int height_, 
	                         const GXPixelFormat &colorFormat_, const GXPixelFormat &depthFormat_, 
							 const GXMultiSampleMode &multiSampleMode_)
{
	this->handle			= 0;
	this->status			= true;
	this->rect.x			= 0;
	this->rect.y			= 0;
	this->rect.width		= width_;
	this->rect.height		= height_;
	this->colorFormat		= colorFormat_;
	this->depthFormat		= depthFormat_;
	this->multiSampleMode	= multiSampleMode_;
}

GXFrameBuffer::~GXFrameBuffer()
{
	const GXFrameBuffer *frameBuffer = GXContext::instance().getFrameBuffer();
	if(frameBuffer==this)
	{
		GXContext::instance().setFrameBuffer(0);
	}
}

bool GXFrameBuffer::getStatus() const
{
	return this->status;
}

int GXFrameBuffer::getWidth() const
{
	return this->rect.width;
}
	
int GXFrameBuffer::getHeight() const
{
	return this->rect.height;
}
	
float GXFrameBuffer::getAspectRatio() const
{
	return ((float)(this->rect.width)) / ((float)(this->rect.height));
}
	
const GXImageRect &GXFrameBuffer::getRectangle() const
{
	return this->rect;
}

const GXPixelFormat &GXFrameBuffer::getColorFormat() const
{
	return this->colorFormat;
}
	
const GXPixelFormat &GXFrameBuffer::getDepthFormat() const
{
	return this->depthFormat;
}

const GXMultiSampleMode &GXFrameBuffer::getMultiSampleMode() const
{
	return this->multiSampleMode;
}

const GXRenderTarget *GXFrameBuffer::getColorTarget() const
{
	return this->colorTarget;
}
	
void GXFrameBuffer::setColorTarget(GXRenderTarget *colorTarget_)
{
	this->colorTarget = colorTarget;
}
	
const GXRenderTarget *GXFrameBuffer::getDepthTarget() const
{
	return this->depthTarget;
}
	
void GXFrameBuffer::setDepthTarget(GXRenderTarget *depthTarget_)
{
	this->depthTarget = depthTarget;
}