///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _AttributesBlock_h_
#define _AttributesBlock_h_

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
using namespace EpicForce;

namespace EpicForce
{

///////////////////////////////////////////////////////////////////
class AttributesBlock
{
public:
	AttributesBlock();
	~AttributesBlock();

	AttributesBlock &operator = (const AttributesBlock &other);
	bool operator == (const AttributesBlock &Attributes) const;

	/*
	bool construct(const Vector<GXShaderAttributeType> &attributeTypes_, 
				   const Vector<GXVertexFormat> &vertexFormats_, 
				   const Vector<String> &attributeNames_, 
				   const Vector<GXVertexStreamSource> &vertexStreamSources_);
	*/

	int getNumAttributes() const;
	const GXShaderAttributeType &getAttributeType(int i) const;
	const GXVertexFormat &getVertexFormat(int i) const;
	const char *AttributesBlock::getAttributeName(int i) const;
	const GXVertexStreamSource &getVertexStreamSource(int i) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	Vector<GXShaderAttributeType>	attributeTypes;
	Vector<GXVertexFormat>			vertexFormats;
	Vector<String>					attributeNames;
	Vector<GXVertexStreamSource>	vertexStreamSources;
};

};

#endif