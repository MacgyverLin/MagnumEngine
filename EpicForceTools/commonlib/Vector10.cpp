///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Vector10.h"
using namespace EpicForce;

const Vector10 Vector10::ZERO    (Vector3::ZERO, Quaternion::ZERO, Vector3::ZERO);
const Vector10 Vector10::IDENTITY(Vector3::ZERO, Quaternion::IDENTITY, Vector3(1, 1, 1));

Vector10::Vector10()
{
	// no init for fast array 
}

Vector10::Vector10(const Vector3 &t_, const Quaternion &q_, const Vector3 &k_)
{
	t = t_;
	q = q_;
	k = k_;
}

Vector10::~Vector10()
{
}

// assignment
Vector10& Vector10::operator= (const Vector10& rkV)
{
	t = rkV.t;
	q = rkV.q;
	k = rkV.k;

	return *this;
}

void Vector10::read(InputStream &is)
{
	is >> t >> q >> k;
}

	// arithmetic operations
Vector10 Vector10::operator+ (const Vector10 &rkV) const
{
    return Vector10(t+rkV.t, q+rkV.q, k+rkV.k);
}

Vector10 Vector10::operator- (const Vector10 &rkV) const
{
	return Vector10(t-rkV.t, q-rkV.q, k-rkV.k);
}

Vector10 Vector10::operator* (float fScalar) const
{
	return Vector10(t*fScalar, q*fScalar, k*fScalar);
}

Vector10 Vector10::operator/ (float fScalar) const
{
	return Vector10(t/fScalar, q/fScalar, k/fScalar);
}

Vector10 Vector10::operator- () const
{
	return Vector10(-t, -q, -k);
}

// arithmetic updates
Vector10 Vector10::operator+= (const Vector10 &rkV)
{
    t += rkV.t;
    q += rkV.q;
    k += rkV.k;
    return *this;
}

Vector10 Vector10::operator-= (const Vector10 &rkV)
{
    t -= rkV.t;
    q -= rkV.q;
    k -= rkV.k;
    return *this;
}

Vector10 Vector10::operator*= (float fScalar)
{
    t *= fScalar;
    q *= fScalar;
    k *= fScalar;
    return *this;
}

Vector10 Vector10::operator/= (float fScalar)
{
    t /= fScalar;
    q /= fScalar;
    k /= fScalar;
    return *this;
}

Vector10 &Vector10::Slerp(float t, const Vector10 &v1, const Vector10 &v2)
{
	this->t = v1.t * t + v2.t * (1-t);
	this->q.Slerp(t, v1.q, v2.q);
	q.Normalize();
	this->k = v1.k * t + v2.k * (1-t);

	return *this;
}

Vector10 &Vector10::Nlerp(float t, const Vector10 &v1, const Vector10 &v2)
{
	this->t = v1.t * t + v2.t * (1-t);
	this->q = v1.q * t + v2.q * (1-t);
	q.Normalize();
	this->k = v1.k * t + v2.k * (1-t);

	return *this;
}

void Vector10::ToMatrix4(Matrix4 &mat) const
{
	/*
	q.ToRotationMatrix(mat);

	mat[0][0] *= k[0];
	mat[0][1] *= k[1];
	mat[0][2] *= k[2];
	mat[0][3]  = t[0];

	mat[1][0] *= k[0];
	mat[1][1] *= k[1];
	mat[1][2] *= k[2];
	mat[1][3]  = t[1];

	mat[2][0] *= k[0];
	mat[2][1] *= k[1]; 
	mat[2][2] *= k[2];
	mat[2][3]  = t[2];

	mat[3][0]  = 0;
	mat[3][1]  = 0;
	mat[3][2]  = 0;
	mat[3][3]  = 1;
	*/

    float fTx  = 2.0f*q[1];
    float fTy  = 2.0f*q[2];
    float fTz  = 2.0f*q[3];
    float fTwx = fTx*q[0];
    float fTwy = fTy*q[0];
    float fTwz = fTz*q[0];
    float fTxx = fTx*q[1];
    float fTxy = fTy*q[1];
    float fTxz = fTz*q[1];
    float fTyy = fTy*q[2];
    float fTyz = fTz*q[2];
    float fTzz = fTz*q[3];

	float *v = (float *)mat;
    v[0]  = (1.0f-(fTyy+fTzz))*k[0];
    v[1]  = ((fTxy+fTwz)     )*k[1];
    v[2]  = ((fTxz-fTwy)     )*k[2];
	v[3]  = t[0];
    
    v[4]  = ((fTxy-fTwz)     )*k[0];
	v[5]  = (1.0f-(fTxx+fTzz))*k[1];
	v[6]  = ((fTyz+fTwx)     )*k[2];
	v[7]  = t[1];
    
	v[8]  = ((fTxz+fTwy)     )*k[0];
    v[9]  = ((fTyz-fTwx)     )*k[1];
    v[10] = (1.0f-(fTxx+fTyy))*k[2];
	v[11] = t[2];

	v[12] = 0;
	v[13] = 0;
	v[14] = 0;
	v[15] = 1;
}

namespace Mayhem
{

//Vector10 operator *(float fScalar, const Vector10& rkV)
//{
	//return rkV * fScalar;
//}

}