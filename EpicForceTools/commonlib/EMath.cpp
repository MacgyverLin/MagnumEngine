///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "EMath.h"
using namespace EpicForce;

const float Math::EPSILON			= FLT_EPSILON;
const float Math::ZERO_TOLERANCE	= 1e-06f;
const float Math::MAX_REAL			= FLT_MAX;
const float Math::MIN_REAL			= -FLT_MAX;
const int   Math::MAX_INT			= MAX_INT;
const int   Math::MIN_INT			= -MAX_INT;
const float Math::ONE_PI			= (float)(4.0*atan(1.0));
const float Math::TWO_PI			= 2.0f*Math::ONE_PI;
const float Math::HALF_PI			= 0.5f*Math::ONE_PI;
const float Math::INV_PI			= 1.0f/Math::ONE_PI;
const float Math::INV_TWO_PI		= 1.0f/Math::TWO_PI;
const float Math::DEG_2_RAD			= Math::ONE_PI/180.0f;
const float Math::RAD_2_DEG			= 180.0f/Math::ONE_PI;

float Math::FastInvSqrt (float fValue)
{
    float fHalf = 0.5f*fValue;
    int i  = *(int*)&fValue;
    i = 0x5f3759df - (i >> 1);
    fValue = *(float*)&i;
    fValue = fValue*(1.5f - fHalf*fValue*fValue);
    return fValue;
}