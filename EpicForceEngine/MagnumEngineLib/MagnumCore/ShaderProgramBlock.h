///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ShaderProgramBlock_h_
#define _ShaderProgramBlock_h_

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

class ShaderProgramBlock
{
public:
	ShaderProgramBlock();
	virtual ~ShaderProgramBlock();

	ShaderProgramBlock &operator = (const ShaderProgramBlock &other);

	void read(InputStream &is);
	void write(OutputStream &os) const;

	String vertexShaderCode;
	String pixelShaderCode;

	int handle;
};

};

#endif