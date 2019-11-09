///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Capsule3_h_
#define _Capsule3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Segment3.h"

namespace Magnum
{

class Capsule3
{
public:
    // construction
    Capsule3 ();  // uninitialized
    Capsule3 (const Segment3& rkSegment, float fRadius);

    Segment3 Segment;
    float Radius;
};

#include "Capsule3.inl"

}

#endif

