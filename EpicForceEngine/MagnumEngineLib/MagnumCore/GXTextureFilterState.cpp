#include "GXTextureFilterState.h"

GXTextureFilterState::GXTextureFilterState(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_)
{
	set(mag_, min_);
}

void GXTextureFilterState::set(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_)
{
	this->mag = mag_;
	this->min = min_;
}

void GXTextureFilterState::setMagFilter(const GXTextureMagFilterMode &mag_)
{
	this->mag = mag_;
}

const GXTextureMagFilterMode &GXTextureFilterState::getMagFilter() const
{
	return this->mag;
}

void GXTextureFilterState::setMinFilter(const GXTextureMinFilterMode &min_)
{
	this->min = min_;
}

const GXTextureMinFilterMode &GXTextureFilterState::getMinFilter() const
{
	return this->min;
}