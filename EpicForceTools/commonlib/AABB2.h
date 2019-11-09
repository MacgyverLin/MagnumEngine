///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _AABB2_h_
#define _AABB2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
{

class AABB2
{
public:
    // construction
    AABB2 ();  // uninitialized

    // The caller must ensure that fXMin <= fXMax and fYMin <= fYMax.  The
    // class will not check for validity of the input.
    AABB2 (float fXMin, float fXMax, float fYMin, float fYMax);

    // Overlap testing is in the strict sense.  If the two boxes are just
    // touching along a common edge, the boxes are reported as overlapping.
    bool HasXOverlap (const AABB2& rkBox) const;
    bool HasYOverlap (const AABB2& rkBox) const;
    bool TestIntersection (const AABB2& rkBox) const;

    // The return value is 'true' if there is overlap.  In this case the
    // intersection is stored in rkIntr.  If the return value is 'false',
    // if there is no overlap.  In this case rkIntr is undefined.
    bool FindIntersection (const AABB2& rkBox,
        AABB2& rkIntr) const;

    Vector2 Min, Max;
};

#include "AABB2.inl"

}

#endif

