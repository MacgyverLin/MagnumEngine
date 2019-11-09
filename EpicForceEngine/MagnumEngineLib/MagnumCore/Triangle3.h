///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Triangle3_h_
#define _Triangle3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace Magnum
{

class Triangle3
{
public:
    // The triangle is represented as an array of three vertices, V0, V1,
    // and V2.

    // construction
    Triangle3 ();  // uninitialized
    Triangle3 (const Vector3& rkV0, const Vector3& rkV1,
        const Vector3& rkV2);
    Triangle3 (const Vector3 akV[3]);

    Vector3 V[3];
};

#include "Triangle3.inl"

}

#endif

