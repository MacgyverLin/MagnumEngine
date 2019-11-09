#include "GXRenderTarget.h"

GXRenderTarget::GXRenderTarget(GXColorBuffer *buffer_)
{
	this->buffer	= buffer_;
	this->level		= 0;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}

GXRenderTarget::GXRenderTarget(GXDepthBuffer *buffer_)
{
	this->buffer	= buffer_;
	this->level		= 0;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}
	
GXRenderTarget::GXRenderTarget(GXTexture2D *texture_, int level_)
{
	this->buffer	= texture_;
	this->level		= level_;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}

GXRenderTarget::GXRenderTarget(GXTextureCube *texture_, int level_, const GXTextureCubeFace &cubeFace_)
{
	this->buffer	= texture_;
	this->level		= level_;
	this->cubeFace	= cubeFace_;
}

void GXRenderTarget::set(GXColorBuffer *buffer_)
{
	this->buffer	= buffer_;
	this->level		= 0;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}

void GXRenderTarget::set(GXDepthBuffer *buffer_)
{
	this->buffer	= buffer_;
	this->level		= 0;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}

void GXRenderTarget::set(GXTexture2D *texture_, int level_)
{
	this->buffer	= texture_;
	this->level		= level_;
	this->cubeFace	= GXTextureCubeFace::PositiveX;
}

void GXRenderTarget::set(GXTextureCube *texture_, int level_, const GXTextureCubeFace &cubeFace_)
{
	this->buffer	= texture_;
	this->level		= level_;
	this->cubeFace	= cubeFace_;
}