///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Lozenge3_h_
#define _Lozenge3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Rectangle3.h"

namespace EpicForce
{


class Lozenge3
{
public:
    // construction
    Lozenge3 ();  // uninitialized
    Lozenge3 (const Rectangle3& rkRectangle, float fRadius);

    Rectangle3 Rectangle;
    float Radius;
};

#include "Lozenge3.inl"

}

#endif

