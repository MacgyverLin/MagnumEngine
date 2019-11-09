///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AABB3_h_
#define _AABB3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace Magnum
{

class AABB3
{
public:
    // construction
    AABB3 ();  // uninitialized

    // The caller must ensure that fXMin <= fXMax and fYMin <= fYMax.  The
    // class will not check for validity of the input.
    AABB3 (float fXMin, float fXMax, float fYMin, float fYMax,
        float fZMin, float fZMax);

    // Overlap testing is in the strict sense.  If the two boxes are just
    // touching along a common edge, the boxes are reported as overlapping.
    bool HasXOverlap (const AABB3& rkBox) const;
    bool HasYOverlap (const AABB3& rkBox) const;
    bool HasZOverlap (const AABB3& rkBox) const;
    bool TestIntersection (const AABB3& rkBox) const;

    // The return value is 'true' if there is overlap.  In this case the
    // intersection is stored in rkIntr.  If the return value is 'false',
    // if there is no overlap.  In this case rkIntr is undefined.
    bool FindIntersection (const AABB3& rkBox,
        AABB3& rkIntr) const;

    Vector3 Min, Max;
};

#include "AABB3.inl"

}

#endif

