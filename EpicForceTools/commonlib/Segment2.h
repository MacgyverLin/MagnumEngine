///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Segment2_h_
#define _Segment2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
{


class Segment2
{
public:
    // The segment is represented as P+t*D, where P is the segment origin,
    // D is a unit-length direction vector and |t| <= e.  The value e is
    // referred to as the extent of the segment.  The end points of the
    // segment are P-e*D and P+e*D.  The user must ensure that the direction
    // vector is unit-length.  The representation for a segment is analogous
    // to that for an oriented bounding box.  P is the center, D is the
    // axis direction, and e is the extent.

    // construction
    Segment2 ();  // uninitialized
    Segment2 (const Vector2& rkOrigin, const Vector2& rkDirection,
        float fExtent);

    // end points
    Vector2 GetPosEnd () const;  // P+e*D
    Vector2 GetNegEnd () const;  // P-e*D

    Vector2 Origin, Direction;
    float Extent;
};

#include "Segment2.inl"

}

#endif

