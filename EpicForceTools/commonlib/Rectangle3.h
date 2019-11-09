///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Rectangle3_h_
#define _Rectangle3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace EpicForce
{

class Rectangle3
{
public:
    // Points are R(s,t) = C+s0*U0+s1*U1, where C is the center of the
    // rectangle, U0 and U1 are unit-length and perpendicular axes.  The
    // parameters s0 and s1 are constrained by |s0| <= e0 and |s1| <= e1,
    // where e0 > 0 and e1 > 0 are called the extents of the rectangle.

    // construction
    Rectangle3 ();  // uninitialized
    Rectangle3 (const Vector3& rkCenter, const Vector3* akAxis,
        const float* afExtent);
    Rectangle3 (const Vector3& rkCenter, const Vector3& rkAxis0,
        const Vector3& rkAxis1, float fExtent0, float fExtent1);

    void ComputeVertices (Vector3 akVertex[4]) const;

    // corners
    Vector3 GetPPCorner () const;  // C + e0*A0 + e1*A1
    Vector3 GetPMCorner () const;  // C + e0*A0 - e1*A1
    Vector3 GetMPCorner () const;  // C - e0*A0 + e1*A1
    Vector3 GetMMCorner () const;  // C - e0*A0 - e1*A1

    Vector3 Center;
    Vector3 Axis[2];
    float Extent[2];
};

#include "Rectangle3.inl"

}

#endif

