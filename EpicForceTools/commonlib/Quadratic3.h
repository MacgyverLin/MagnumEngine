///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Quadratic3_h_
#define _Quadratic3_h_

#include "Stage.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Matrix3.h"

namespace EpicForce
{

class Quadratic3
{
public:
    // A quadratic function of three variables x, y, and z is
    //   Q(x,y,z) = a0 + a1*x + a2*y + a3*z + a4*x*x + a5*x*y + a6*x*z +
    //              a7*y*y + a8*y*z + a9*z*z
    // This class is a simple wrapper for storing the coefficients and for
    // evaluating the function.

    // Construction and destruction.  The default constructor initializes the
    // coefficients to zero.
    Quadratic3 ();
    Quadratic3 (float fA0, float fA1, float fA2, float fA3, float fA4, float fA5,
        float fA6, float fA7, float fA8, float fA9);
    Quadratic3 (const float afA[10]);

    // Access coefficients as an array.
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);

    // Access coefficients by variable name.
    float Constant() const;  // a0
    float& Constant();
    float X() const;         // a1
    float& X();
    float Y() const;         // a2
    float& Y();
    float Z() const;         // a3
    float& Z();
    float XX() const;        // a4
    float& XX();
    float XY() const;        // a5
    float& XY();
    float XZ() const;        // a6
    float& XZ();
    float YY() const;        // a7
    float& YY();
    float YZ() const;        // a8
    float& YZ();
    float ZZ() const;        // a9
    float& ZZ();

    // Access coefficients by variable powers.  The valid powers are
    // (xorder,yorder,zorder) in {(0,0,0),(1,0,0),(0,1,0),(0,0,1),(2,0,0),
    // (1,1,0),(1,0,1),(0,2,0),(0,1,1),(0,0,2)}.  The Set method ignores an
    // invalid triple.  The Get method returns zero on an invalid triple.
    void Set (int iXOrder, int iYOrder, int iZOrder, float fCoeff);
    float Get (int iXOrder, int iYOrder, int iZOrder) const;

    // Evaluate Q(x,y,z).
    float operator() (float fX, float fY, float fZ) const;
    float operator() (const Vector3& rkP) const;

    // Transformations intended to modify the level sets of Q(X) = 0.  A
    // level set point X may be transformed by Y = R*S*X+T, where S is a
    // diagonal matrix of positive scales, R is a rotation matrix, and T is
    // a translation vector.  The new level set has points Y which are the
    // solution to P(Y) = 0, where
    //   P(Y) = Q(X) = Q(Inverse(S)*Transpose(R)*(Y-T))
    // The following functions compute the coefficients for P(Y), where the
    // scale matrix is represented as a 3-tuple.

    // Compute P(Y) = Q(Y-T).
    Quadratic3 Translate (const Vector3& rkTrn) const;

    // Compute P(Y) = Q(Transpose(R)*Y).
    Quadratic3 Rotate (const Matrix3& rkRot) const;

    // Compute P(Y) = Q(Inverse(S)*Y).
    Quadratic3 Scale (const Vector3& rkScale) const;

    // TO DO.  Add classification code to decide what type of set is defined
    // by Q(x,y,z) = 0.  Add factorization code.

private:
    float m_afCoeff[10];
};

#include "Quadratic3.inl"

}

#endif

