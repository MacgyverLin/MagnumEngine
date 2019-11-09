///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Segment3_h_
#define _Segment3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace EpicForce
{

class Segment3
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
    Segment3 ();  // uninitialized
    Segment3 (const Vector3& rkOrigin, const Vector3& rkDirection,
        float fExtent);

    // end points
    Vector3 GetPosEnd () const;  // P+e*D
    Vector3 GetNegEnd () const;  // P-e*D

    Vector3 Origin, Direction;
    float Extent;
};

#include "Segment3.inl"

}

#endif

