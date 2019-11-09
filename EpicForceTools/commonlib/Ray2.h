///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Ray2_h_
#define _Ray2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
{

class Ray2
{
public:
    // The ray is represented as P+t*D, where P is the ray origin, D is a
    // unit-length direction vector, and t >= 0.  The user must ensure that
    // the direction vector satisfies this condition.

    // construction
    Ray2 ();  // uninitialized
    Ray2 (const Vector2& rkOrigin, const Vector2& rkDirection);

    Vector2 Origin, Direction;
};

#include "Ray2.inl"

}

#endif

