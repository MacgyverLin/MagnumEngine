///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SingleCurve3.h"
//#include "Integrate1.h"

namespace Magnum
{
//----------------------------------------------------------------------------

SingleCurve3::SingleCurve3 (float fTMin, float fTMax)
    :
    Curve3(fTMin,fTMax)
{
}
//----------------------------------------------------------------------------

float SingleCurve3::GetSpeedWithData (float fTime, void* pvData)
{
    return ((Curve3*)pvData)->GetSpeed(fTime);
}
//----------------------------------------------------------------------------

float SingleCurve3::GetLength (float fT0, float fT1) const
{
    assert(m_fTMin <= fT0 && fT0 <= m_fTMax);
    assert(m_fTMin <= fT1 && fT1 <= m_fTMax);
    assert(fT0 <= fT1);

    // return Integrate1::RombergIntegral(8,fT0,fT1,GetSpeedWithData, (void*)this);
	assert(0);
	return 0;
}
//----------------------------------------------------------------------------

float SingleCurve3::GetTime (float fLength, int iIterations,
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
    float fOmRatio = (float)1.0 - fRatio;
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
