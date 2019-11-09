///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
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
#ifdef ENABLE_RESOURCE_IMPORT
#include "tinyxml.h"
#endif

namespace EpicForce
{

class UniformsBlock
{
public:
	UniformsBlock();
	virtual ~UniformsBlock();

	UniformsBlock &operator = (const UniformsBlock &other);

	int getNumUniforms() const;
	int getUniformIdx(const char *name) const;
	int getUniformIdxBySemantic(const char *sematic) const;
	GXUniform &getUniform(const char *name);
	GXUniform &getUniformBySemantic(const char *name);
	GXUniform &getUniform(int i);

	void read(InputStream &is);
	void write(OutputStream &os) const;

	Vector<GXUniform>	uniforms;
};

};

#endif
