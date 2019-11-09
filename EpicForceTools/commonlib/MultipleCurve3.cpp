///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "MultipleCurve3.h"

namespace EpicForce
{
//----------------------------------------------------------------------------

MultipleCurve3::MultipleCurve3 (int iSegments, float* afTime)
    :
    Curve3(afTime[0],afTime[iSegments])
{
    m_iSegments = iSegments;
    m_afTime = afTime;
    m_afLength = 0;
    m_afAccumLength = 0;
}
//----------------------------------------------------------------------------

MultipleCurve3::~MultipleCurve3 ()
{
    delete[] m_afTime;
    delete[] m_afLength;
    delete[] m_afAccumLength;
}
//----------------------------------------------------------------------------

int MultipleCurve3::GetSegments () const
{
    return m_iSegments;
}
//----------------------------------------------------------------------------

const float* MultipleCurve3::GetTimes () const
{
    return m_afTime;
}
//----------------------------------------------------------------------------

void MultipleCurve3::GetKeyInfo (float fTime, int& riKey, float& rfDt)
    const
{
    if (fTime <= m_afTime[0])
    {
        riKey = 0;
        rfDt = (float)0.0;
    }
    else if (fTime >= m_afTime[m_iSegments])
    {
        riKey = m_iSegments-1;
        rfDt = m_afTime[m_iSegments] - m_afTime[m_iSegments-1];
    }
    else
    {
        for (int i = 0; i < m_iSegments; i++)
        {
            if (fTime < m_afTime[i+1])
            {
                riKey = i;
                rfDt = fTime - m_afTime[i];
                break;
            }
        }
    }
}
//----------------------------------------------------------------------------

float MultipleCurve3::GetSpeedWithData (float fTime, void* pvData)
{
    MultipleCurve3* pvThis = *(MultipleCurve3**) pvData;
    int iKey = *(int*)((char*)pvData + sizeof(pvThis));
    return pvThis->GetSpeedKey(iKey,fTime);
}
//----------------------------------------------------------------------------

void MultipleCurve3::InitializeLength () const
{
    m_afLength = new float[m_iSegments];
    m_afAccumLength = new float[m_iSegments];

    // arc lengths of the segments
    int iKey;
    for (iKey = 0; iKey < m_iSegments; iKey++)
    {
        m_afLength[iKey] = GetLengthKey(iKey,(float)0.0,
            m_afTime[iKey+1]-m_afTime[iKey]);
    }

    // accumulative arc length
    m_afAccumLength[0] = m_afLength[0];
    for (iKey = 1; iKey < m_iSegments; iKey++)
    {
        m_afAccumLength[iKey] = m_afAccumLength[iKey-1] + m_afLength[iKey];
    }
}
//----------------------------------------------------------------------------

float MultipleCurve3::GetLength (float fT0, float fT1) const
{
    assert(m_fTMin <= fT0 && fT0 <= m_fTMax);
    assert(m_fTMin <= fT1 && fT1 <= m_fTMax);
    assert(fT0 <= fT1);

    if (!m_afLength)
    {
        InitializeLength();
    }

    int iKey0, iKey1;
    float fDt0, fDt1;
    GetKeyInfo(fT0,iKey0,fDt0);
    GetKeyInfo(fT1,iKey1,fDt1);

    float fLength;
    if (iKey0 < iKey1)
    {
        // accumulate full-segment lengths
        fLength = (float)0.0;
        for (int i = iKey0+1; i < iKey1; i++)
        {
            fLength += m_afLength[i];
        }
        
        // add on partial first segment
        fLength += GetLengthKey(iKey0,fDt0,m_afTime[iKey0+1]-m_afTime[iKey0]);
        
        // add on partial last segment
        fLength += GetLengthKey(iKey1,(float)0.0,fDt1);
    }
    else
    {
        fLength = GetLengthKey(iKey0,fDt0,fDt1);
    }

    return fLength;
}
//----------------------------------------------------------------------------

float MultipleCurve3::GetTime (float fLength, int iIterations,
    float fTolerance) const
{
    if (!m_afLength)
    {
        InitializeLength();
    }

    if (fLength <= (float)0.0)
    {
        return m_fTMin;
    }

    if (fLength >= m_afAccumLength[m_iSegments-1])
    {
        return m_fTMax;
    }

    int iKey;
    for (iKey = 0; iKey < m_iSegments; iKey++)
    {
        if (fLength < m_afAccumLength[iKey])
        {
            break;
        }
    }
    if (iKey >= m_iSegments)
    {
        return m_afTime[m_iSegments];
    }

    // try Newton's method first for rapid convergence
    float fL0, fL1;
    if (iKey == 0)
    {
        fL0 = fLength;
        fL1 = m_afAccumLength[0];
    }
    else
    {
        fL0 = fLength - m_afAccumLength[iKey-1];
        fL1 = m_afAccumLength[iKey] - m_afAccumLength[iKey-1];
    }

    // use Newton's method to invert the arc length integral
    float fDt1 = m_afTime[iKey+1] - m_afTime[iKey];
    float fDt0 = fDt1*fL0/fL1;
    for (int i = 0; i < iIterations; i++)
    {
        float fDifference = GetLengthKey(iKey,(float)0.0,fDt0) - fL0;
        if (Math::FAbs(fDifference) <= fTolerance)
        {
            return m_afTime[iKey] + fDt0;
        }

        fDt0 -= fDifference/GetSpeedKey(iKey,fDt0);
    }

    // Newton's method failed.  If this happens, increase iterations or
    // tolerance or integration accuracy.
    return Math::MAX_REAL;
}
//----------------------------------------------------------------------------

float MultipleCurve3::GetVariation (float fT0, float fT1,
    const Vector3* pkP0, const Vector3* pkP1) const
{
    assert(m_fTMin <= fT0 && fT0 <= m_fTMax);
    assert(m_fTMin <= fT1 && fT1 <= m_fTMax);
    assert(fT0 <= fT1);

    // construct line segment, A + (t-t0)*B
    Vector3 kP0, kP1;
    if (!pkP0)
    {
        kP0 = GetPosition(fT0);
        pkP0 = &kP0;
    }
    if (!pkP1)
    {
        kP1 = GetPosition(fT1);
        pkP1 = &kP1;
    }
    float fInvDT = ((float)1.0)/(fT1 - fT0);
    Vector3 kA, kB = fInvDT*(*pkP1 - *pkP0);

    int iKey0, iKey1;
    float fDt0, fDt1;
    GetKeyInfo(fT0,iKey0,fDt0);
    GetKeyInfo(fT1,iKey1,fDt1);

    float fVariation;
    if (iKey0 < iKey1)
    {
        // accumulate full-segment variations
        fVariation = (float)0.0;
        for (int i = iKey0+1; i < iKey1; i++)
        {
            kA = *pkP0 + (m_afTime[i] - fT0)*kB;
            fVariation += GetVariationKey(i,(float)0.0,
                m_afTime[i+1]-m_afTime[i],kA,kB);
        }
        
        // add on partial first segment
        kA = *pkP0 + (m_afTime[iKey0] - fT0)*kB;
        fVariation += GetVariationKey(iKey0,fDt0,
            m_afTime[iKey0+1]-m_afTime[iKey0],kA,kB);
        
        // add on partial last segment
        kA = *pkP0 + (m_afTime[iKey1] - fT0)*kB;
        fVariation += GetVariationKey(iKey1,0.0f,fDt1,kA,kB);
    }
    else
    {
        kA = *pkP0 + (m_afTime[iKey0] - fT0)*kB;
        fVariation = GetVariationKey(iKey0,fDt0,fDt1,kA,kB);
    }

    return fVariation;
}
//----------------------------------------------------------------------------
}

