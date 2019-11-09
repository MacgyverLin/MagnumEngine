///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Capsule3_h_
#define _Capsule3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Segment3.h"

namespace EpicForce
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

