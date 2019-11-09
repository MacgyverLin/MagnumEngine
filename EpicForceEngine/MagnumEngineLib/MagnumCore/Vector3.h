///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR3_H
#define VECTOR3_H

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Vector3
{
public:
    // construction
    Vector3 ();  // uninitialized
    Vector3 (float fX, float fY, float fZ);
    Vector3 (const float* afTuple);
    Vector3 (const Vector3& rkV);

	void Set (float fX, float fY, float fZ);

    // coordinate access
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();
    float Z () const;
    float& Z ();

    // assignment
    Vector3& operator= (const Vector3& rkV);

    // comparison
    bool operator== (const Vector3& rkV) const;
    bool operator!= (const Vector3& rkV) const;
    bool operator<  (const Vector3& rkV) const;
    bool operator<= (const Vector3& rkV) const;
    bool operator>  (const Vector3& rkV) const;
    bool operator>= (const Vector3& rkV) const;

    // arithmetic operations
    Vector3 operator+ (const Vector3& rkV) const;
    Vector3 operator- (const Vector3& rkV) const;
	Vector3 operator* (const Vector3& rkV) const;
    Vector3 operator* (float fScalar) const;
    Vector3 operator/ (float fScalar) const;
    Vector3 operator- () const;

    // arithmetic updates
    Vector3& operator+= (const Vector3& rkV);
    Vector3& operator-= (const Vector3& rkV);
	Vector3& operator*= (const Vector3& rkV);
    Vector3& operator*= (float fScalar);
    Vector3& operator/= (float fScalar);

    // vector operations
    float Length () const;
    float SquaredLength () const;
    float Dot (const Vector3& rkV) const;
    float Normalize ();

    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    Vector3 Cross (const Vector3& rkV) const;
    Vector3 UnitCross (const Vector3& rkV) const;

    // Compute the barycentric coordinates of the point with respect to the
    // tetrahedron <V0,V1,V2,V3>, P = b0*V0 + b1*V1 + b2*V2 + b3*V3, where
    // b0 + b1 + b2 + b3 = 1.
    void GetBarycentrics (const Vector3& rkV0,
        const Vector3& rkV1, const Vector3& rkV2,
        const Vector3& rkV3, float afBary[4]) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors
    // U, V, and W and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW);
    static void Orthonormalize (Vector3* akV);

    // Input W must be initialized to a nonzero vector, output is {U,V,W},
    // an orthonormal basis.  A hint is provided about whether or not W
    // is already unit length.
    static void GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
        Vector3& rkW, bool bUnitLengthW);

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector3* akPoint,
        Vector3& rkMin, Vector3& rkMax);

    // special vectors
    static const Vector3 ZERO;    // (0,0,0)
    static const Vector3 UNIT_X;  // (1,0,0)
    static const Vector3 UNIT_Y;  // (0,1,0)
    static const Vector3 UNIT_Z;  // (0,0,1)
    static const Vector3 ONE;     // (1,1,1)

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const Vector3& rkV) const;

    float m_afTuple[3];
};

#include "Vector3.inl"

};

#endif
