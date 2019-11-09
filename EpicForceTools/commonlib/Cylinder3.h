///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Cylinder3_h_
#define _Cylinder3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Segment3.h"

namespace EpicForce
{

class Cylinder3
{
public:
    // Cylinder line segment has end points C-(H/2)*D and C+(H/2)*D where
    // D is a unit-length vector.  H is infinity for infinite cylinder.

    // construction
    Cylinder3 ();  // uninitialized
    Cylinder3 (const Segment3& rkSegment, float fHeight, float fRadius);

    Segment3 Segment;
    float Height, Radius;
};

#include "Cylinder3.inl"

}

#endif

