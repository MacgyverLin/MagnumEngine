///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _EMath_h_
#define _EMath_h_

#include "Stage.h"

namespace EpicForce
{

class Math
{
public:
    // Wrappers to hide implementations of functions.  The ACos and ASin
    // functions clamp the input argument to [-1,1] to avoid NaN issues
    // when the input is slightly larger than 1 or slightly smaller than -1.
    // Other functions have the potential for using a fast and approximate
    // algorithm rather than calling the standard math library functions.
    static float ACos (float fValue);
    static float ASin (float fValue);
    static float ATan (float fValue);
    static float ATan2 (float fY, float fX);
    static float Ceil (float fValue);
    static float Cos (float fValue);
    static float Exp (float fValue);
    static float FAbs (float fValue);
    static float Floor (float fValue);
    static float FMod (float fX, float fY);
    static float InvSqrt (float fValue);
    static float Log (float fValue);
    static float Pow (float fBase, float fExponent);
    static float Sin (float fValue);
    static float Sqr (float fValue);
    static float Sqrt (float fValue);
    static float Tan (float fValue);

    static float Min (float fX, float fY);
    static float Max (float fX, float fY);   
	static float Clamp (float fX, float fMin, float fMax);

    // Return -1 if the input is negative, 0 if the input is zero, and +1
    // if the input is positive.
    static int Sign (int iValue);
    static float Sign (float fValue);

    // Generate a random number in [0,1).  The random number generator may
    // be seeded by a first call to UnitRandom with a positive seed.
    static float UnitRandom (unsigned int uiSeed = 0);

    // Generate a random number in [-1,1).  The random number generator may
    // be seeded by a first call to SymmetricRandom with a positive seed.
    static float SymmetricRandom (unsigned int uiSeed = 0);

    // Generate a random number in [min,max).  The random number generator may
    // be seeded by a first call to IntervalRandom with a positive seed.
    static float IntervalRandom (float fMin, float fMax,
        unsigned int uiSeed = 0);

	static unsigned int CeilPower2(unsigned int x);
	static bool isPowerOf2(unsigned int v);

    // Fast evaluation of trigonometric and inverse trigonometric functions
    // using polynomial approximations.  The speed ups were measured on an
    // AMD 2800 (2.08 GHz) processor using Visual Studion .NET 2003 with a
    // release build.

    // The input must be in [0,pi/2].
    // max error sin0 = 1.7e-04, speed up = 4.0
    // max error sin1 = 1.9e-08, speed up = 2.8
    static float FastSin0 (float fAngle);
    static float FastSin1 (float fAngle);

    // The input must be in [0,pi/2]
    // max error cos0 = 1.2e-03, speed up = 4.5
    // max error cos1 = 6.5e-09, speed up = 2.8
    static float FastCos0 (float fAngle);
    static float FastCos1 (float fAngle);

    // The input must be in [0,pi/4].
    // max error tan0 = 8.1e-04, speed up = 5.6
    // max error tan1 = 1.9e-08, speed up = 3.4
    static float FastTan0 (float fAngle);
    static float FastTan1 (float fAngle);

    // The input must be in [0,1].
    // max error invsin0 = 6.8e-05, speed up = 7.5
    // max error invsin1 = 1.4e-07, speed up = 5.5
    static float FastInvSin0 (float fValue);
    static float FastInvSin1 (float fValue);

    // The input must be in [0,1].
    // max error invcos0 = 6.8e-05, speed up = 7.5
    // max error invcos1 = 1.4e-07, speed up = 5.7
    static float FastInvCos0 (float fValue);
    static float FastInvCos1 (float fValue);

    // The input must be in [-1,1]. 
    // max error invtan0 = 1.2e-05, speed up = 2.8
    // max error invtan1 = 2.3e-08, speed up = 1.8
    static float FastInvTan0 (float fValue);
    static float FastInvTan1 (float fValue);

    // A fast approximation to 1/sqrt.
    static float FastInvSqrt (float fValue);

    // common constants
    static const float EPSILON;
    static const float ZERO_TOLERANCE;
    static const float MAX_REAL;
	static const float MIN_REAL;
    static const int   MAX_INT;
	static const int   MIN_INT;
    static const float ONE_PI;
    static const float TWO_PI;
    static const float HALF_PI;
    static const float INV_PI;
    static const float INV_TWO_PI;
    static const float DEG_2_RAD;
    static const float RAD_2_DEG;
};

#include "EMath.inl"

//----------------------------------------------------------------------------

// Fast conversion from a IEEE 32-bit floating point number F in [0,1] to a
// a 32-bit integer I in [0,2^L-1].
//
//   fFloat = F
//   iLog = L
//   iInt = I

#define WM3_SCALED_FLOAT_TO_INT(fFloat,iLog,iInt)\
{ \
    int iShift = 150 - iLog - ((*(int*)(&fFloat) >> 23) & 0xFF); \
    if (iShift < 24) \
    { \
        iInt = ((*(int*)(&fFloat) & 0x007FFFFF) | \
            0x00800000) >> iShift; \
        if (iInt == (1 << iLog)) \
        { \
            iInt--; \
        } \
    } \
    else \
    { \
        iInt = 0; \
    } \
}

//----------------------------------------------------------------------------

};

#endif

