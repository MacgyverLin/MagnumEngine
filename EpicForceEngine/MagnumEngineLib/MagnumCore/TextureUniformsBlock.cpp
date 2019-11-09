///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "TextureUniformsBlock.h"
using namespace Magnum;

static const char *defaultSemantics[] =
{
	"DIFFUSEMAP",
	"OPACITYMAP",
	"SPECULARMAP",
	"NORMALMAP",
	"LIGHTMAP",
	"DISPLACEMENTMAP",
	"REFLECTIONMAP",
	"RENDERCOLORTARGET",
	"RENDERDEPTHSTENCILTARGET",
	"WORLD",
	"WORLDINVERSE",
	"VIEW",
	"VIEWINVERSE",
	"PROJECTION",
	"PROJECTIONINVERSE",
	"WORLDVIEW",
	"WORLDVIEWINVERSE",
	"VIEWPROJ",
	"VIEWPROJINVERSE",
	"WORLDVIEWPROJ",
	"WORLDVIEWPROJINVERSE",
	"VIEWPORTPIXELSIZE",
	"LOCALBBOXMIN",
	"LOCALBBOXMAX",
	"LOCALBBOXSIZE",
	"RECIPLOCALBBOXSIZE",
	"LIGHT0VECTOR",
	"LIGHT0COLOR",
	"LIGHT0ATTENUATION",
	"LIGHT1VECTOR",
	"LIGHT1COLOR",
	"LIGHT1ATTENUATION",
	"LIGHT2VECTOR",
	"LIGHT2COLOR",
	"LIGHT2ATTENUATION",
	"TIME",
	"PERIOD",
	"BONETRANSFORMS",
};

TextureUniformsBlock::TextureUniformsBlock()
{
}

TextureUniformsBlock::~TextureUniformsBlock()
{
}

TextureUniformsBlock &TextureUniformsBlock::operator = (const TextureUniformsBlock &other)
{
	names					= other.names;
	semantics				= other.semantics;
	textures				= other.textures;
	minFilters				= other.minFilters;
	magFilters				= other.magFilters;
	wrapSs					= other.wrapSs;
	wrapTs					= other.wrapTs;

	return *this;
}

int	TextureUniformsBlock::getNumTextures() const
{
	return textures.length();
}

int	TextureUniformsBlock::getTextureHandle(const char *name) const
{
	for(int i=0; i<names.length(); i++)
	{
		if(names[i]==name)
			return i;
	}

	return -1;
}

int	TextureUniformsBlock::getTextureHandleBySemantic(const char *semantic) const
{
	for(int i=0; i<semantics.length(); i++)
	{
		if(semantics[i]==semantic)
			return i;
	}

	return -1;
}

TextureBase *TextureUniformsBlock::getTexture(int handle)
{
	if(handle>=0 && handle<textures.length())
		return (TextureBase	*)textures[handle];
	else
		return 0;
}

void TextureUniformsBlock::setTexture(int handle, TextureBase *texture_)
{
	if(handle>=0 && handle<textures.length())
		textures[handle] = (void *)texture_;
}

GXTextureMinFilterMode TextureUniformsBlock::getMinFilters(int handle) const
{
	if(handle>=0 && handle<textures.length())
		return minFilters[handle];
	else
		return GXTextureMinFilterMode::Nearest;
}

GXTextureMagFilterMode TextureUniformsBlock::getMagFilters(int handle) const
{
	if(handle>=0 && handle<textures.length())
		return magFilters[handle];
	else
		return GXTextureMagFilterMode::Nearest;
}

GXTextureWrapMode TextureUniformsBlock::getWrapS(int handle) const
{
	if(handle>=0 && handle<wrapSs.length())
		return wrapSs[handle];
	else
		return GXTextureWrapMode::Repeat;
}

GXTextureWrapMode TextureUniformsBlock::getWrapT(int handle) const
{
	if(handle>=0 && handle<wrapTs.length())
		return wrapTs[handle];
	else
		return GXTextureWrapMode::Repeat;
}

void TextureUniformsBlock::read(InputStream &is)
{
	VectorRead<String> namesVectorRead(names);
	is >> namesVectorRead;

	VectorRead<String> semanticsVectorRead(semantics);
	is >> semanticsVectorRead;

	int numTextures;
	is >> numTextures;
	textures.resize(numTextures);

	VectorRead<GXTextureMinFilterMode> minFiltersVectorRead(minFilters);
	is >> minFiltersVectorRead;

	VectorRead<GXTextureMagFilterMode> magFiltersVectorRead(magFilters);
	is >> magFiltersVectorRead;

	VectorRead<GXTextureWrapMode> wrapSsVectorRead(wrapSs);
	is >> wrapSsVectorRead;

	VectorRead<GXTextureWrapMode> wrapTsVectorRead(wrapTs);
	is >> wrapTsVectorRead;
}

void TextureUniformsBlock::write(OutputStream &os) const
{
	VectorWrite<String> namesVectorWrite(names);
	os << namesVectorWrite;

	VectorWrite<String> semanticsVectorWrite(semantics);
	os << semanticsVectorWrite;

	int numTextures = textures.length();
	os << numTextures;

	VectorWrite<GXTextureMinFilterMode> minFiltersVectorWrite(minFilters);
	os << minFiltersVectorWrite;

	VectorWrite<GXTextureMagFilterMode> magFiltersVectorWrite(magFilters);
	os << magFiltersVectorWrite;

	VectorWrite<GXTextureWrapMode> wrapSsVectorWrite(wrapSs);
	os << wrapSsVectorWrite;

	VectorWrite<GXTextureWrapMode> wrapTsVectorWrite(wrapTs);
	os << wrapTsVectorWrite;
}