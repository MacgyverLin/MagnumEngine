///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Circle2_h_
#define _Circle2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
{

class Circle2
{
public:
    // construction
    Circle2 ();  // uninitialized
    Circle2 (const Vector2& rkCenter, float fRadius);

    Vector2 Center;
    float Radius;
};

#include "Circle2.inl"

}

#endif

