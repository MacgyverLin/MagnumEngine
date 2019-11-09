///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Quaternion_h_
#define _Quaternion_h_

#include "Stage.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Matrix4.h"

namespace EpicForce
{

class Quaternion
{
public:
    // A quaternion is q = w + x*i + y*j + z*k where (w,x,y,z) is not
    // necessarily a unit length vector in 4D.

    // construction
    Quaternion ();  // uninitialized
    Quaternion (float fW, float fX, float fY, float fZ);
    Quaternion (const Quaternion& rkQ);

    // quaternion for the input rotation matrix
    Quaternion (const Matrix4& rkRot);

    // quaternion for the rotation of the axis-angle pair
    Quaternion (const Vector3& rkAxis, float fAngle);

    // quaternion for the rotation matrix with specified columns
    Quaternion (const Vector3 akRotColumn[3]);

	void Set (float fW, float fX, float fY, float fZ);

    // member access:  0 = w, 1 = x, 2 = y, 3 = z
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);
    float W () const;
    float& W ();
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();
    float Z () const;
    float& Z ();

    // assignment
    Quaternion& operator= (const Quaternion& rkQ);

    // comparison
    bool operator== (const Quaternion& rkQ) const;
    bool operator!= (const Quaternion& rkQ) const;
    bool operator<  (const Quaternion& rkQ) const;
    bool operator<= (const Quaternion& rkQ) const;
    bool operator>  (const Quaternion& rkQ) const;
    bool operator>= (const Quaternion& rkQ) const;

    // arithmetic operations
    Quaternion operator+ (const Quaternion& rkQ) const;
    Quaternion operator- (const Quaternion& rkQ) const;
    Quaternion operator* (const Quaternion& rkQ) const;
    Quaternion operator* (float fScalar) const;
    Quaternion operator/ (float fScalar) const;
    Quaternion operator- () const;

    // arithmetic updates
    Quaternion& operator+= (const Quaternion& rkQ);
    Quaternion& operator-= (const Quaternion& rkQ);
    Quaternion& operator*= (float fScalar);
    Quaternion& operator/= (float fScalar);

    // conversion between quaternions, matrices, and axis-angle
    Quaternion& FromRotationMatrix (const Matrix4& rkRot);
    void ToRotationMatrix (Matrix4& rkRot) const; //checked
    Quaternion& FromRotationMatrix (const Vector3 akRotColumn[3]);
    void ToRotationMatrix (Vector3 akRotColumn[3]) const;//checked
    Quaternion& FromAxisAngle (const Vector3& rkAxis, float fAngle);
    void ToAxisAngle (Vector3& rkAxis, float& rfAngle) const;
	
	void ToEulerZXY(float &Z, float &X, float &Y);

    // functions of a quaternion
    float Length () const;  // length of 4-tuple
    float SquaredLength () const;  // squared length of 4-tuple
    float Dot (const Quaternion& rkQ) const;  // dot product of 4-tuples
    float Normalize ();  // make the 4-tuple unit length
    Quaternion Inverse () const;  // apply to non-zero quaternion
    Quaternion Conjugate () const;
    Quaternion Exp () const;  // apply to quaternion with w = 0
    Quaternion Log () const;  // apply to unit-length quaternion

    // rotation of a vector by a quaternion
    Vector3 Rotate (const Vector3& rkVector) const;

    // spherical linear interpolation
    Quaternion& Slerp (float fT, const Quaternion& rkP, const Quaternion& rkQ);

    Quaternion& SlerpExtraSpins (float fT, const Quaternion& rkP,
        const Quaternion& rkQ, int iExtraSpins);

    // intermediate terms for spherical quadratic interpolation
    Quaternion& Intermediate (const Quaternion& rkQ0,
        const Quaternion& rkQ1, const Quaternion& rkQ2);

    // spherical quadratic interpolation
    Quaternion& Squad (float fT, const Quaternion& rkQ0,
        const Quaternion& rkA0, const Quaternion& rkA1,
        const Quaternion& rkQ1);

    // Compute a quaternion that rotates unit-length vector V1 to unit-length
    // vector V2.  The rotation is about the axis perpendicular to both V1 and
    // V2, with angle of that between V1 and V2.  If V1 and V2 are parallel,
    // any axis of rotation will do, such as the permutation (z2,x2,y2), where
    // V2 = (x2,y2,z2).
    Quaternion& Align (const Vector3& rkV1, const Vector3& rkV2);

    // Decompose a quaternion into q = q_twist * q_swing, where q is 'this'
    // quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
    // q, q_swing represents the rotation about the axis perpendicular to
    // V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1.
    void DecomposeTwistTimesSwing (const Vector3& rkV1,
        Quaternion& rkTwist, Quaternion& rkSwing);

    // Decompose a quaternion into q = q_swing * q_twist, where q is 'this'
    // quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
    // q, q_swing represents the rotation about the axis perpendicular to
    // V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1.
    void DecomposeSwingTimesTwist (const Vector3& rkV1,
        Quaternion& rkSwing, Quaternion& rkTwist);

    // special values
    static const Quaternion IDENTITY;  // the identity rotation
    static const Quaternion ZERO;

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const Quaternion& rkQ) const;

    // support for FromRotationMatrix
    static int ms_iNext[3];

    float m_afTuple[4];
};

Quaternion operator* (float fScalar, const Quaternion& rkQ);

#include "Quaternion.inl"

};

#endif

