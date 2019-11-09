///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline float Math::ACos (float fValue)
{
    if ( -(float)1.0 < fValue )
    {
        if ( fValue < (float)1.0 )
            return (float)acos((double)fValue);
        else
            return (float)0.0;
    }
    else
    {
        return ONE_PI;
    }
}

//----------------------------------------------------------------------------
inline float Math::ASin (float fValue)
{
    if ( -(float)1.0 < fValue )
    {
        if ( fValue < (float)1.0 )
            return (float)asin((double)fValue);
        else
            return HALF_PI;
    }
    else
    {
        return -HALF_PI;
    }
}

//----------------------------------------------------------------------------
inline float Math::ATan (float fValue)
{
    return (float)atan((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::ATan2 (float fY, float fX)
{
    return (float)atan2((double)fY,(double)fX);
}

//----------------------------------------------------------------------------
inline float Math::Ceil (float fValue)
{
    return (float)ceil((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Cos (float fValue)
{
    return (float)cos((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Exp (float fValue)
{
    return (float)exp((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::FAbs (float fValue)
{
    return (float)fabs((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Floor (float fValue)
{
    return (float)floor((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::FMod (float fX, float fY)
{
    return (float)fmod((double)fX,(double)fY);
}

//----------------------------------------------------------------------------
inline float Math::InvSqrt (float fValue)
{
    return (float)(1.0/sqrt((double)fValue));
}

//----------------------------------------------------------------------------
inline float Math::Log (float fValue)
{
    return (float)log((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Pow (float fBase, float fExponent)
{
    return (float)pow((double)fBase,(double)fExponent);
}

//----------------------------------------------------------------------------
inline float Math::Sin (float fValue)
{
    return (float)sin((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Sqr (float fValue)
{
    return fValue*fValue;
}

//----------------------------------------------------------------------------
inline float Math::Sqrt (float fValue)
{
    return (float)sqrt((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Tan (float fValue)
{
    return (float)tan((double)fValue);
}

//----------------------------------------------------------------------------
inline float Math::Min (float fX, float fY)
{
	if(fX>fY)
		return fY;
	else
		return fX;
}

//----------------------------------------------------------------------------
inline float Math::Max (float fX, float fY)
{
	if(fX<fY)
		return fY;
	else
		return fX;
}

//----------------------------------------------------------------------------
inline float Math::Clamp (float fX, float fMin, float fMax)
{
	return Min( Max(fX, fMin), fMax );
}

//----------------------------------------------------------------------------
inline int Math::Sign (int iValue)
{
    if ( iValue > 0 )
        return 1;

    if ( iValue < 0 )
        return -1;

    return 0;
}

//----------------------------------------------------------------------------
inline float Math::Sign (float fValue)
{
    if ( fValue > (float)0.0 )
        return (float)1.0;

    if ( fValue < (float)0.0 )
        return -(float)1.0;

    return (float)0.0;
}

//----------------------------------------------------------------------------
inline float Math::UnitRandom (unsigned int uiSeed )
{
    if ( uiSeed > 0 )
        srand(uiSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (float)dRatio;
}

//----------------------------------------------------------------------------
inline float Math::SymmetricRandom (unsigned int uiSeed)
{
    if ( uiSeed > 0.0 )
        srand(uiSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (float)(2.0*dRatio - 1.0);
}

//----------------------------------------------------------------------------
inline float Math::IntervalRandom (float fMin, float fMax, unsigned int uiSeed)
{
    if ( uiSeed > 0 )
        srand(uiSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fMin+(fMax-fMin)*((float)dRatio);
}

//----------------------------------------------------------------------------
inline unsigned int Math::CeilPower2(unsigned int x) 
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >>16);

	return x + 1;
}

//----------------------------------------------------------------------------
inline bool Math::isPowerOf2(unsigned int v)
{
	return (v & (v - 1)) == 0;
}

//----------------------------------------------------------------------------
inline float Math::FastSin0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)7.61e-03;
    fResult *= fASqr;
    fResult -= (float)1.6605e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastSin1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = -(float)2.39e-08;
    fResult *= fASqr;
    fResult += (float)2.7526e-06;
    fResult *= fASqr;
    fResult -= (float)1.98409e-04;
    fResult *= fASqr;
    fResult += (float)8.3333315e-03;
    fResult *= fASqr;
    fResult -= (float)1.666666664e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastCos0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)3.705e-02;
    fResult *= fASqr;
    fResult -= (float)4.967e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastCos1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = -(float)2.605e-07;
    fResult *= fASqr;
    fResult += (float)2.47609e-05;
    fResult *= fASqr;
    fResult -= (float)1.3888397e-03;
    fResult *= fASqr;
    fResult += (float)4.16666418e-02;
    fResult *= fASqr;
    fResult -= (float)4.999999963e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastTan0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)2.033e-01;
    fResult *= fASqr;
    fResult += (float)3.1755e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastTan1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)9.5168091e-03;
    fResult *= fASqr;
    fResult += (float)2.900525e-03;
    fResult *= fASqr;
    fResult += (float)2.45650893e-02;
    fResult *= fASqr;
    fResult += (float)5.33740603e-02;
    fResult *= fASqr;
    fResult += (float)1.333923995e-01;
    fResult *= fASqr;
    fResult += (float)3.333314036e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvSin0 (float fValue)
{
    float fRoot = Math::Sqrt(((float)1.0)-fValue);
    float fResult = -(float)0.0187293;
    fResult *= fValue;
    fResult += (float)0.0742610;
    fResult *= fValue;
    fResult -= (float)0.2121144;
    fResult *= fValue;
    fResult += (float)1.5707288;
    fResult = HALF_PI - fRoot*fResult;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvSin1 (float fValue)
{
    float fRoot = Math::Sqrt(FAbs(((float)1.0)-fValue));
    float fResult = -(float)0.0012624911;
    fResult *= fValue;
    fResult += (float)0.0066700901;
    fResult *= fValue;
    fResult -= (float)0.0170881256;
    fResult *= fValue;
    fResult += (float)0.0308918810;
    fResult *= fValue;
    fResult -= (float)0.0501743046;
    fResult *= fValue;
    fResult += (float)0.0889789874;
    fResult *= fValue;
    fResult -= (float)0.2145988016;
    fResult *= fValue;
    fResult += (float)1.5707963050;
    fResult = HALF_PI - fRoot*fResult;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvCos0 (float fValue)
{
    float fRoot = Math::Sqrt(((float)1.0)-fValue);
    float fResult = -(float)0.0187293;
    fResult *= fValue;
    fResult += (float)0.0742610;
    fResult *= fValue;
    fResult -= (float)0.2121144;
    fResult *= fValue;
    fResult += (float)1.5707288;
    fResult *= fRoot;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvCos1 (float fValue)
{
    float fRoot = Math::Sqrt(FAbs(((float)1.0)-fValue));
    float fResult = -(float)0.0012624911;
    fResult *= fValue;
    fResult += (float)0.0066700901;
    fResult *= fValue;
    fResult -= (float)0.0170881256;
    fResult *= fValue;
    fResult += (float)0.0308918810;
    fResult *= fValue;
    fResult -= (float)0.0501743046;
    fResult *= fValue;
    fResult += (float)0.0889789874;
    fResult *= fValue;
    fResult -= (float)0.2145988016;
    fResult *= fValue;
    fResult += (float)1.5707963050;
    fResult *= fRoot;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvTan0 (float fValue)
{
    float fVSqr = fValue*fValue;
    float fResult = (float)0.0208351;
    fResult *= fVSqr;
    fResult -= (float)0.085133;
    fResult *= fVSqr;
    fResult += (float)0.180141;
    fResult *= fVSqr;
    fResult -= (float)0.3302995;
    fResult *= fVSqr;
    fResult += (float)0.999866;
    fResult *= fValue;
    return fResult;
}

//----------------------------------------------------------------------------
inline float Math::FastInvTan1 (float fValue)
{
    float fVSqr = fValue*fValue;
    float fResult = (float)0.0028662257;
    fResult *= fVSqr;
    fResult -= (float)0.0161657367;
    fResult *= fVSqr;
    fResult += (float)0.0429096138;
    fResult *= fVSqr;
    fResult -= (float)0.0752896400;
    fResult *= fVSqr;
    fResult += (float)0.1065626393;
    fResult *= fVSqr;
    fResult -= (float)0.1420889944;
    fResult *= fVSqr;
    fResult += (float)0.1999355085;
    fResult *= fVSqr;
    fResult -= (float)0.3333314528;
    fResult *= fVSqr;
    fResult += (float)1.0;
    fResult *= fValue;
    return fResult;
}
