///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _UniformsBlock_h_
#define _UniformsBlock_h_

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

namespace Magnum
{

class UniformsBlock
{
public:
	UniformsBlock();
	virtual ~UniformsBlock();

	UniformsBlock &operator = (const UniformsBlock &other);

	int getNumUniforms() const;
	int getUniformHandle(const char *name) const;
	int getUniformHandleBySemantic(const char *sematic) const;
	GXUniform &getUniform(int handle);

	void read(InputStream &is);
	void write(OutputStream &os) const;

	Vector<GXUniform>	uniforms;
};

};

#endif
