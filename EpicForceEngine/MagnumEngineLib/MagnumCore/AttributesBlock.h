///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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
using namespace Magnum;

namespace Magnum
{

///////////////////////////////////////////////////////////////////////////////////
class AttributesBlock
{
public:
	AttributesBlock();
	~AttributesBlock();

	AttributesBlock &operator = (const AttributesBlock &other);
	bool operator == (const AttributesBlock &Attributes) const;

	int getNumAttributes() const;
	const GXShaderAttributeType &getAttributeType(int i) const;
	const GXVertexFormat &getVertexFormat(int i) const;
	const char *getAttributeName(int i) const;
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