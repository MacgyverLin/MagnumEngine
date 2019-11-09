///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Quadratic2_h_
#define _Quadratic2_h_

#include "Stage.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Matrix2.h"

namespace EpicForce
{


class Quadratic2
{
public:
    // A quadratic function of two variables x and y is
    //   Q(x,y) = a0 + a1*x + a2*y + a3*x*x + a4*x*y + a5*y*y
    // This class is a simple wrapper for storing the coefficients and for
    // evaluating the function.

    // Construction and destruction.  The default constructor initializes the
    // coefficients to zero.
    Quadratic2 ();
    Quadratic2 (float fA0, float fA1, float fA2, float fA3, float fA4, float fA5);
    Quadratic2 (const float afA[6]);

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
    float XX() const;        // a3
    float& XX();
    float XY() const;        // a4
    float& XY();
    float YY() const;        // a5
    float& YY();

    // Access coefficients by variable powers.  The valid powers are
    // (xorder,yorder) in {(0,0),(1,0),(0,1),(2,0),(1,1),(0,2)}.  The Set
    // method ignores an invalid pair.  The Get method returns zero on an
    // invalid pair.
    void Set (int iXOrder, int iYOrder, float fCoeff);
    float Get (int iXOrder, int iYOrder) const;

    // Evaluate Q(x,y).
    float operator() (float fX, float fY) const;
    float operator() (const Vector2& rkP) const;

    // Transformations intended to modify the level sets of Q(X) = 0.  A
    // level set point X may be transformed by Y = R*S*X+T, where S is a
    // diagonal matrix of positive scales, R is a rotation matrix, and T is
    // a translation vector.  The new level set has points Y which are the
    // solution to P(Y) = 0, where
    //   P(Y) = Q(X) = Q(Inverse(S)*Transpose(R)*(Y-T))
    // The following functions compute the coefficients for P(Y), where the
    // scale matrix is represented as a 2-tuple.

    // Compute P(Y) = Q(Y-T).
    Quadratic2 Translate (const Vector2& rkTrn) const;

    // Compute P(Y) = Q(Transpose(R)*Y).
    Quadratic2 Rotate (const Matrix2& rkRot) const;

    // Compute P(Y) = Q(Inverse(S)*Y).
    Quadratic2 Scale (const Vector2& rkScale) const;

    // TO DO.  Add classification code to decide what type of set is defined
    // by Q(x,y) = 0.  Add factorization code.

private:
    float m_afCoeff[6];
};

#include "Quadratic2.inl"

}

#endif

