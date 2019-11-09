///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Plane3_h_
#define _Plane3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace Magnum
{

class Plane3
{
public:
    // The plane is represented as Dot(N,X) = c where N is a unit-length
    // normal vector, c is the plane constant, and X is any point on the
    // plane.  The user must ensure that the normal vector satisfies this
    // condition.

    Plane3 ();  // uninitialized
    Plane3 (const Plane3& rkPlane);

    // specify N and c directly
    Plane3 (const Vector3& rkNormal, float fConstant);

    // N is specified, c = Dot(N,P) where P is on the plane
    Plane3 (const Vector3& rkNormal, const Vector3& rkP);

    // N = Cross(P1-P0,P2-P0)/Length(Cross(P1-P0,P2-P0)), c = Dot(N,P0) where
    // P0, P1, P2 are points on the plane.
    Plane3 (const Vector3& rkP0, const Vector3& rkP1,
        const Vector3& rkP2);

    // assignment
    Plane3& operator= (const Plane3& rkPlane);

    // The "positive side" of the plane is the half space to which the plane
    // normal points.  The "negative side" is the other half space.  The
    // function returns +1 for the positive side, -1 for the negative side,
    // and 0 for the point being on the plane.
    int WhichSide (const Vector3& rkP) const;

    // Compute d = Dot(N,Q)-c where N is the plane normal and c is the plane
    // constant.  This is a signed distance.  The sign of the return value is
    // positive if the point is on the positive side of the plane, negative if
    // the point is on the negative side, and zero if the point is on the
    // plane.
    float DistanceTo (const Vector3& rkQ) const;

	bool isCoplanar(const Plane3& rkPlane) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

    Vector3 Normal;
    float Constant;
};

#include "Plane3.inl"

};

#endif

