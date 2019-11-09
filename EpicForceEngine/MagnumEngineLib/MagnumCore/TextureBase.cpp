///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "TextureBase.h"
using namespace Magnum;

TextureBase::TextureBase()
: filterState(GXTextureMagFilterMode::Linear, GXTextureMinFilterMode::Linear)
, wrapState(GXTextureWrapMode::Repeat, GXTextureWrapMode::Repeat)
{
}

TextureBase::~TextureBase()
{
}

void TextureBase::setMinFilterMode(const GXTextureMinFilterMode &minFilter_)
{
	filterState.setMinFilter(minFilter_);
}

void TextureBase::setMagFilterMode(const GXTextureMagFilterMode &magFilter_)
{
	filterState.setMagFilter(magFilter_);
}

const GXTextureMinFilterMode &TextureBase::getMinFilterMode() const
{
	return filterState.getMinFilter();
}

const GXTextureMagFilterMode &TextureBase::getMagFilterMode() const
{
	return filterState.getMagFilter();
}

void TextureBase::setWrapS(const GXTextureWrapMode &wrapS_)
{
	wrapState.setWrapS(wrapS_);
}

const GXTextureWrapMode &TextureBase::getWrapS() const
{
	return wrapState.getWrapS();
}

void TextureBase::setWrapT(const GXTextureWrapMode &wrapT_)
{
	wrapState.setWrapS(wrapT_);
}

const GXTextureWrapMode &TextureBase::getWrapT() const
{
	return wrapState.getWrapT();
}