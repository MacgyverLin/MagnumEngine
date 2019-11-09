///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "SingleCurve2.h"
//#include "Integrate1.h"

namespace EpicForce
{
//----------------------------------------------------------------------------

SingleCurve2::SingleCurve2 (float fTMin, float fTMax)
    :
    Curve2(fTMin,fTMax)
{
}
//----------------------------------------------------------------------------

float SingleCurve2::GetSpeedWithData (float fTime, void* pvData)
{
    return ((Curve2*)pvData)->GetSpeed(fTime);
}
//----------------------------------------------------------------------------

float SingleCurve2::GetLength (float fT0, float fT1) const
{
    assert(m_fTMin <= fT0 && fT0 <= m_fTMax);
    assert(m_fTMin <= fT1 && fT1 <= m_fTMax);
    assert(fT0 <= fT1);

    //return Integrate1::RombergIntegral(8,fT0,fT1,GetSpeedWithData, (void*)this);
	assert(0);
	return 0;
}
//----------------------------------------------------------------------------

float SingleCurve2::GetTime (float fLength, int iIterations,
    float fTolerance) const
{
    if (fLength <= (float)0.0)
    {
        return m_fTMin;
    }

    if (fLength >= GetTotalLength())
    {
        return m_fTMax;
    }

    // initial guess for Newton's method
    float fRatio = fLength/GetTotalLength();
    float fOmRatio = ((float)1.0) - fRatio;
    float fTime = fOmRatio*m_fTMin + fRatio*m_fTMax;

    for (int i = 0; i < iIterations; i++)
    {
        float fDifference = GetLength(m_fTMin,fTime) - fLength;
        if (Math::FAbs(fDifference) < fTolerance)
        {
            return fTime;
        }

        fTime -= fDifference/GetSpeed(fTime);
    }

    // Newton's method failed.  If this happens, increase iterations or
    // tolerance or integration accuracy.
    return Math::MAX_REAL;
}
//----------------------------------------------------------------------------

}

