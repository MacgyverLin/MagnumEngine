///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Triangle3_h_
#define _Triangle3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace EpicForce
{

class Triangle3
{
public:
    // The triangle is represented as an array of three vertices, V0, V1,
    // and V2.

    // construction
    Triangle3 ();  // uninitialized
    Triangle3 (const Vector3& rkV0, const Vector3& rkV1,
        const Vector3& rkV2);
    Triangle3 (const Vector3 akV[3]);

    Vector3 V[3];
};

#include "Triangle3.inl"

}

#endif

