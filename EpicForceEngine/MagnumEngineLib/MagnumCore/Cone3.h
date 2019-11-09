///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Cone3_h_
#define _Cone3_h_

#include "Vector3.h"
#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Cone3
{
public:
    // An acute cone is Dot(A,X-V) = |X-V| cos(T) where V is the vertex, A
    // is the unit-length direction of the axis of the cone, and T is the
    // cone angle with 0 < T < PI/2.  The cone interior is defined by the
    // inequality Dot(A,X-V) >= |X-V| cos(T).  Since cos(T) > 0, we can avoid
    // computing square roots.  The solid cone is defined by the inequality
    // Dot(A,X-V)^2 >= Dot(X-V,X-V) cos(T)^2.

    // construction
    Cone3 ();  // uninitialized
    Cone3 (const Vector3& rkVertex, const Vector3& rkAxis,
        float fAngle);
    Cone3 (const Vector3& rkVertex, const Vector3& rkAxis,
        float fCosAngle, float fSinAngle);

    Vector3 Vertex;
    Vector3 Axis;
    float CosAngle, SinAngle;  // cos(T), sin(T)
};

#include "Cone3.inl"

}

#endif

