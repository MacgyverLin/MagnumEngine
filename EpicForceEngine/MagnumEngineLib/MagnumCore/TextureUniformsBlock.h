///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TextureUniformsBlock_h_
#define _TextureUniformsBlock_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "AttributesBlock.h"
#include "RenderStatesBlock.h"
#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "GXDef.h"
#include "BVector2.h"
#include "BVector3.h"
#include "BVector4.h"
#include "IVector2.h"
#include "IVector3.h"
#include "IVector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector10.h"
#include "ColorRGBA.h"
#include "GXUniform.h"
#include "TextureBase.h"

namespace Magnum
{

class TextureUniformsBlock
{
public:
	TextureUniformsBlock();
	virtual ~TextureUniformsBlock();

	TextureUniformsBlock &operator = (const TextureUniformsBlock &other);

	int								getNumTextures() const;
	int								getTextureHandle(const char *name) const;
	int								getTextureHandleBySemantic(const char *semantic) const;
	TextureBase						*getTexture(int handle);
	void							setTexture(int handle, TextureBase *texture);

	GXTextureMinFilterMode			getMinFilters(int handle) const;
	GXTextureMagFilterMode			getMagFilters(int handle) const;
	GXTextureWrapMode				getWrapS(int handle) const;
	GXTextureWrapMode				getWrapT(int handle) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	Vector<String>					names;
	Vector<String>					semantics;
	Vector<void *> 					textures;

	Vector<GXTextureMinFilterMode>	minFilters;
	Vector<GXTextureMagFilterMode>	magFilters;
	Vector<GXTextureWrapMode>		wrapSs;
	Vector<GXTextureWrapMode>		wrapTs;
};

};

#endif
