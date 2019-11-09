///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Circle3_h_
#define _Circle3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace EpicForce
{

class Circle3
{
public:
    // Plane containing circle is Dot(N,X-C) = 0 where X is any point in the
    // plane.  Vectors U, V, and N form an orthonormal right-handed set
    // (matrix [U V N] is orthonormal and has determinant 1).  Circle within
    // the plane is parameterized by X = C + R*(cos(A)*U + sin(A)*V) where
    // A is an angle in [0,2*pi).

    // construction
    Circle3 ();  // uninitialized
    Circle3 (const Vector3& rkCenter, const Vector3& rkU,
        const Vector3& rkV, const Vector3& rkN, float fRadius);

    Vector3 Center, U, V, N;
    float Radius;
};

#include "Circle3.inl"

}

#endif

