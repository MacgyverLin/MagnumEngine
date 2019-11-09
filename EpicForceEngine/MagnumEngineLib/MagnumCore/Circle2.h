///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Circle2_h_
#define _Circle2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace Magnum
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

