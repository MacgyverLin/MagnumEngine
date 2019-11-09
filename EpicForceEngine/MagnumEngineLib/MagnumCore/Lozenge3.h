///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Lozenge3_h_
#define _Lozenge3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Rectangle3.h"

namespace Magnum
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

