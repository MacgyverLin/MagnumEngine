///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _VertexDesc_h_
#define _VertexDesc_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
//#include "Component.h"
//#include "ResourceImport.h"
//#include "ResourceAccess.h"
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

class TiXmlNode;

namespace EpicForce
{

///////////////////////////////////////////////////////////////////
class VertexDesc
{
public:
	VertexDesc();
	~VertexDesc();

	bool construct(const Vector<GXVertexFormat> &vertexFormats_, 
				   const Vector<GXVertexStreamSource> &vertexStreamSources_);

	int numAttributes() const;
	const GXVertexFormat &getVertexFormat(int i) const;
	const GXVertexStreamSource &getVertexStreamSource(int i) const;

	bool operator == (const VertexDesc &vertexDesc) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	Vector<GXVertexFormat>			vertexFormats;
	Vector<GXVertexStreamSource>	vertexStreamSources;
};

};

#endif