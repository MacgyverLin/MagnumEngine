///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Triangle2_h_
#define _Triangle2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace Magnum
{

class Triangle2
{
public:
    // The triangle is represented as an array of three vertices, V0, V1,
    // and V2.

    // construction
    Triangle2 ();  // uninitialized
    Triangle2 (const Vector2& rkV0, const Vector2& rkV1,
        const Vector2& rkV2);
    Triangle2 (const Vector2 akV[3]);

    Vector2 V[3];
};

#include "Triangle2.inl"

}

#endif

