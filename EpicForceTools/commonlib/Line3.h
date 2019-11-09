///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Line3_h_
#define _Line3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace EpicForce
{

class Line3
{
public:
    // The line is represented as P+t*D where P is the line origin and D is
    // a unit-length direction vector.  The user must ensure that the
    // direction vector satisfies this condition.

    // construction
    Line3 ();  // uninitialized
    Line3 (const Vector3& rkOrigin, const Vector3& rkDirection);

    Vector3 Origin, Direction;
};

#include "Line3.inl"

}

#endif

