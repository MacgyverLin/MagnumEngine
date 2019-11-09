///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Cylinder3_h_
#define _Cylinder3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Segment3.h"

namespace Magnum
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

