///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Vector4_h_
#define _Vector4_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class Vector4
{
public:
    // construction
    Vector4 ();  // uninitialized
    Vector4 (float fX, float fY, float fZ, float fW);
    Vector4 (const float* afTuple);
    Vector4 (const Vector4& rkV);

	void Set (float fX, float fY, float fZ, float fW);

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
    float W () const;
    float& W ();

    // assignment
    Vector4& operator= (const Vector4& rkV);

    // comparison
    bool operator== (const Vector4& rkV) const;
    bool operator!= (const Vector4& rkV) const;
    bool operator<  (const Vector4& rkV) const;
    bool operator<= (const Vector4& rkV) const;
    bool operator>  (const Vector4& rkV) const;
    bool operator>= (const Vector4& rkV) const;

    // arithmetic operations
    Vector4 operator+ (const Vector4& rkV) const;
    Vector4 operator- (const Vector4& rkV) const;
    Vector4 operator* (float fScalar) const;
    Vector4 operator/ (float fScalar) const;
    Vector4 operator- () const;

    // arithmetic updates
    Vector4& operator+= (const Vector4& rkV);
    Vector4& operator-= (const Vector4& rkV);
    Vector4& operator*= (float fScalar);
    Vector4& operator/= (float fScalar);

    // vector operations
    float Length () const;
    float SquaredLength () const;
    float Dot (const Vector4& rkV) const;
    float Normalize ();

    // special vectors
    static const Vector4 ZERO;    // (0,0,0,0)
    static const Vector4 UNIT_X;  // (1,0,0,0)
    static const Vector4 UNIT_Y;  // (0,1,0,0)
    static const Vector4 UNIT_Z;  // (0,0,1,0)
    static const Vector4 UNIT_W;  // (0,0,0,1)
    static const Vector4 ONE;     // (1,1,1,1)
	
	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const Vector4& rkV) const;

    float m_afTuple[4];
};

// arithmetic operations
Vector4 operator* (float fScalar, const Vector4& rkV);

#include "Vector4.inl"

};

#endif
