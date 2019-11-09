///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BaryCentric_h_
#define _BaryCentric_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Magnum
{

class BaryCentric
{
public:
    BaryCentric(const Vector3 &a_, const Vector3 &b_, const Vector3 &c_);

	Vector2 getBaryCentricPoint(const Vector3 &p) const;
	Vector3 getPoint(const Vector2 &uv) const;

	bool isInside(const Vector3 &p) const;
private:
	Vector3 a;
	Vector3 b;
	Vector3 c;
};

};

#endif
