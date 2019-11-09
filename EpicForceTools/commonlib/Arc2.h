///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Arc2_h_
#define _Arc2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Circle2.h"

namespace EpicForce
{

class Arc2 : public Circle2
{
public:
    // The arc is defined by two points End0 and End1 on the circle so that
    // End1 is obtained from End0 by traversing counterclockwise.  The
    // application is responsible for ensuring that End0 and End1 are on the
    // circle and that they are properly ordered.

    Arc2 ();  // uninitialized
    Arc2 (const Vector2& rkCenter, float fRadius,
        const Vector2& rkEnd0, const Vector2& rkEnd1);

    // Test if P is on the arc.  The application must ensure that P is on the
    // circle; that is, |P-C| = R.  This test works regardless of the angle
    // between B-C and A-C.
    bool Contains (const Vector2& rkP) const;

    // Compute the angles formed by the end points with the positive x-axis.
    // The angles are in the interval [0,2*pi).
    float GetAngleEnd0 () const;
    float GetAngleEnd1 () const;

    // The angle spanned by the arc, in [0,2*pi).
    float GetAngle () const;

    Vector2 End0, End1;
    Vector2 Center;
};

#include "Arc2.inl"

}

#endif

