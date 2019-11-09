///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Triangle2_h_
#define _Triangle2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
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

