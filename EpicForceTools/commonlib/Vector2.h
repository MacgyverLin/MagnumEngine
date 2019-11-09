///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Vector2_h_
#define _Vector2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class Vector2
{
public:
    // construction
    Vector2 ();  // uninitialized
    Vector2 (float fX, float fY);
    Vector2 (const float* afTuple);
    Vector2 (const Vector2& rkV);

	void Set(float fX, float fY);

    // coordinate access
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();

    // assignment
    Vector2& operator= (const Vector2& rkV);

    // comparison
    bool operator== (const Vector2& rkV) const;
    bool operator!= (const Vector2& rkV) const;
    bool operator<  (const Vector2& rkV) const;
    bool operator<= (const Vector2& rkV) const;
    bool operator>  (const Vector2& rkV) const;
    bool operator>= (const Vector2& rkV) const;

    // arithmetic operations
    Vector2 operator+ (const Vector2& rkV) const;
    Vector2 operator- (const Vector2& rkV) const;
    Vector2 operator* (float fScalar) const;
    Vector2 operator/ (float fScalar) const;
    Vector2 operator- () const;

    // arithmetic updates
    Vector2& operator+= (const Vector2& rkV);
    Vector2& operator-= (const Vector2& rkV);
    Vector2& operator*= (float fScalar);
    Vector2& operator/= (float fScalar);

    // vector operations
    float Length () const;
    float SquaredLength () const;
    float Dot (const Vector2& rkV) const;
    float Normalize ();

    // returns (y,-x)
    Vector2 Perp () const;

    // returns (y,-x)/sqrt(x*x+y*y)
    Vector2 UnitPerp () const;

    // returns DotPerp((x,y),(V.x,V.y)) = x*V.y - y*V.x
    float DotPerp (const Vector2& rkV) const;

    // Compute the barycentric coordinates of the point with respect to the
    // triangle <V0,V1,V2>, P = b0*V0 + b1*V1 + b2*V2, where b0 + b1 + b2 = 1.
    void GetBarycentrics (const Vector2& rkV0,
        const Vector2& rkV1, const Vector2& rkV2,
        float afBary[3]) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors U
    // and V and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector2& rkU, Vector2& rkV);

    // Input V must be initialized to a nonzero vector, output is {U,V}, an
    // orthonormal basis.  A hint is provided about whether or not V is
    // already unit length.
    static void GenerateOrthonormalBasis (Vector2& rkU, Vector2& rkV,
        bool bUnitLengthV);

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector2* akPoint,
        Vector2& rkMin, Vector2& rkMax);

    // special vectors
    static const Vector2 ZERO;    // (0,0)
    static const Vector2 UNIT_X;  // (1,0)
    static const Vector2 UNIT_Y;  // (0,1)
    static const Vector2 ONE;     // (1,1)
    static const Vector2 NULL_;    // (NAN,NAN)

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const Vector2& rkV) const;

    float m_afTuple[2];
};

#include "Vector2.inl"

};

#endif
