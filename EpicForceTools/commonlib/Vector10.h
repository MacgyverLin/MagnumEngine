///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Vector10_h_
#define _Vector10_h_

#include "Stage.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "InputStream.h"

namespace EpicForce
{

class Vector10 
{
public:
	Vector10();
	Vector10(const Vector3 &t_, const Quaternion &q_, const Vector3 &k_);
	~Vector10();

    // assignment
    Vector10& operator= (const Vector10& rkV);
	void read(InputStream &is);

	// arithmetic operations
    Vector10 operator+ (const Vector10& rkV) const;
    Vector10 operator- (const Vector10& rkV) const;
    Vector10 operator* (float fScalar) const;
    Vector10 operator/ (float fScalar) const;
    Vector10 operator- () const;

    // arithmetic updates
    Vector10 operator+= (const Vector10& rkV);
    Vector10 operator-= (const Vector10& rkV);
    Vector10 operator*= (float fScalar);
    Vector10 operator/= (float fScalar);

	Vector10 &Slerp(float t, const Vector10 &v1, const Vector10 &v2);
	Vector10 &Nlerp(float t, const Vector10 &v1, const Vector10 &v2);
	void ToMatrix4(Matrix4 &mat_) const;

	static const Vector10 ZERO;
	static const Vector10 IDENTITY;

	Vector3			t;	//Translation
	Quaternion		q;	//Rotation
	Vector3			k;	//Scale
};

};

// Vector10 operator* (float fScalar, const Vector10& rkV);

#endif