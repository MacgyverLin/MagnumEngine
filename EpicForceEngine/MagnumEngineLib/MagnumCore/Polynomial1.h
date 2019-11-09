///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Polynomial1_h_
#define _Polynomial1_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Polynomial1
{
public:
    // construction and destruction
    Polynomial1 (int iDegree = -1);
    Polynomial1 (const Polynomial1& rkPoly);
    ~Polynomial1 ();

    // member access
    void SetDegree (int iDegree);
    int GetDegree () const;
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);

    // assignment
    Polynomial1& operator= (const Polynomial1& rkPoly);

    // evaluation
    float operator() (float fT) const;

    // arithmetic operations
    Polynomial1 operator+ (const Polynomial1& rkPoly) const;
    Polynomial1 operator- (const Polynomial1& rkPoly) const;
    Polynomial1 operator* (const Polynomial1& rkPoly) const;
    Polynomial1 operator+ (float fScalar) const;  // input is degree 0 poly
    Polynomial1 operator- (float fScalar) const;  // input is degree 0 poly
    Polynomial1 operator* (float fScalar) const;
    Polynomial1 operator/ (float fScalar) const;
    Polynomial1 operator- () const;

    // arithmetic updates
    Polynomial1& operator += (const Polynomial1& rkPoly);
    Polynomial1& operator -= (const Polynomial1& rkPoly);
    Polynomial1& operator *= (const Polynomial1& rkPoly);
    Polynomial1& operator += (float fScalar);  // input is degree 0 poly
    Polynomial1& operator -= (float fScalar);  // input is degree 0 poly
    Polynomial1& operator *= (float fScalar);
    Polynomial1& operator /= (float fScalar);

    // derivation
    Polynomial1 GetDerivative () const;

    // inversion ( invpoly[i] = poly[degree-i] for 0 <= i <= degree )
    Polynomial1 GetInversion () const;

    // Reduce degree by eliminating all (nearly) zero leading coefficients
    // and by making the leading coefficient one.  The input parameter is
    // the threshold for specifying that a coefficient is effectively zero.
    void Compress (float fEpsilon);

    // If 'this' is P(t) and the divisor is D(t) with degree(P) >= degree(D),
    // then P(t) = Q(t)*D(t)+R(t) where Q(t) is the quotient with
    // degree(Q) = degree(P) - degree(D) and R(t) is the remainder with
    // degree(R) < degree(D).  If this routine is called with
    // degree(P) < degree(D), then Q = 0 and R = P are returned.  The value
    // of epsilon is used as a threshold on the coefficients of the remainder
    // polynomial.  If smaller, the coefficient is assumed to be zero.
    void Divide (const Polynomial1& rkDiv, Polynomial1& rkQuot,
        Polynomial1& rkRem, float fEpsilon) const;

protected:
    int m_iDegree;
    float* m_afCoeff;
};

Polynomial1 operator* (float fScalar, const Polynomial1& rkPoly);

#include "Polynomial1.inl"

}

#endif

