#include "GXTextureWrapState.h"

GXTextureWrapState::GXTextureWrapState(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_)
{
	set(wrapS_, wrapT_);
}

void GXTextureWrapState::set(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_)
{
	this->wrapS = wrapS_;
	this->wrapT = wrapT_;
}

void GXTextureWrapState::setWrapS(const GXTextureWrapMode &wrapS_)
{
	this->wrapS = wrapS_;
}

const GXTextureWrapMode &GXTextureWrapState::getWrapS() const
{
	return this->wrapS;
}

void GXTextureWrapState::setWrapT(const GXTextureWrapMode &wrapT_)
{
	this->wrapT = wrapT_;
}

const GXTextureWrapMode &GXTextureWrapState::getWrapT() const
{
	return this->wrapT;
}