///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "TCBSpline2.h"
//#include "Integrate1.h"
#include "Polynomial1.h"

namespace EpicForce
{
//----------------------------------------------------------------------------

TCBSpline2::TCBSpline2 (int iSegments, float* afTime,
    Vector2* akPoint, float* afTension, float* afContinuity, float* afBias)
    :
    MultipleCurve2(iSegments,afTime)
{
    // TO DO.  Add 'boundary type' just as in natural splines.
    assert(m_iSegments >= 3);

    // all four of these arrays have m_iSegments+1 elements
    m_akPoint = akPoint;
    m_afTension = afTension;
    m_afContinuity = afContinuity;
    m_afBias = afBias;

    m_akA = new Vector2[m_iSegments];
    m_akB = new Vector2[m_iSegments];
    m_akC = new Vector2[m_iSegments];
    m_akD = new Vector2[m_iSegments];

    // For now, treat the first point as if it occurred twice.
    ComputePoly(0,0,1,2);

    for (int i = 1; i < m_iSegments-1; i++)
    {
        ComputePoly(i-1,i,i+1,i+2);
    }

    // For now, treat the last point as if it occurred twice.
    ComputePoly(m_iSegments-2,m_iSegments-1,m_iSegments,m_iSegments);
}
//----------------------------------------------------------------------------

TCBSpline2::~TCBSpline2 ()
{
    delete[] m_akPoint;
    delete[] m_afTension;
    delete[] m_afContinuity;
    delete[] m_afBias;
    delete[] m_akA;
    delete[] m_akB;
    delete[] m_akC;
    delete[] m_akD;
}
//----------------------------------------------------------------------------

const Vector2* TCBSpline2::GetPoints () const
{
    return m_akPoint;
}
//----------------------------------------------------------------------------

const float* TCBSpline2::GetTensions () const
{
    return m_afTension;
}
//----------------------------------------------------------------------------

const float* TCBSpline2::GetContinuities () const
{
    return m_afContinuity;
}
//----------------------------------------------------------------------------

const float* TCBSpline2::GetBiases () const
{
    return m_afBias;
}
//----------------------------------------------------------------------------

void TCBSpline2::ComputePoly (int i0, int i1, int i2, int i3)
{
    Vector2 kDiff = m_akPoint[i2] - m_akPoint[i1];
    float fDt = m_afTime[i2] - m_afTime[i1];

    // build multipliers at P1
    float fOmt0 = (float)1.0 - m_afTension[i1];
    float fOmc0 = (float)1.0 - m_afContinuity[i1];
    float fOpc0 = (float)1.0 + m_afContinuity[i1];
    float fOmb0 = (float)1.0 - m_afBias[i1];
    float fOpb0 = (float)1.0 + m_afBias[i1];
    float fAdj0 = ((float)2.0)*fDt/(m_afTime[i2]-m_afTime[i0]);
    float fOut0 = ((float)0.5)*fAdj0*fOmt0*fOpc0*fOpb0;
    float fOut1 = ((float)0.5)*fAdj0*fOmt0*fOmc0*fOmb0;

    // build outgoing tangent at P1
    Vector2 kTOut = fOut1*kDiff + fOut0*(m_akPoint[i1] - m_akPoint[i0]);

    // build multipliers at point P2
    float fOmt1 = (float)1.0 - m_afTension[i2];
    float fOmc1 = (float)1.0 - m_afContinuity[i2];
    float fOpc1 = (float)1.0 + m_afContinuity[i2];
    float fOmb1 = (float)1.0 - m_afBias[i2];
    float fOpb1 = (float)1.0 + m_afBias[i2];
    float fAdj1 = ((float)2.0)*fDt/(m_afTime[i3] - m_afTime[i1]);
    float fIn0 = ((float)0.5)*fAdj1*fOmt1*fOmc1*fOpb1;
    float fIn1 = ((float)0.5)*fAdj1*fOmt1*fOpc1*fOmb1;

    // build incoming tangent at P2
    Vector2 kTIn = fIn1*(m_akPoint[i3] - m_akPoint[i2]) + fIn0*kDiff;

    m_akA[i1] = m_akPoint[i1];
    m_akB[i1] = kTOut;
    m_akC[i1] = ((float)3.0)*kDiff - ((float)2.0)*kTOut - kTIn;
    m_akD[i1] = ((float)-2.0)*kDiff + kTOut + kTIn;
}
//----------------------------------------------------------------------------

Vector2 TCBSpline2::GetPosition (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector2 kResult = m_akA[iKey] + fDt*(m_akB[iKey] +
        fDt*(m_akC[iKey] + fDt*m_akD[iKey]));

    return kResult;
}
//----------------------------------------------------------------------------

Vector2 TCBSpline2::GetFirstDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector2 kResult = m_akB[iKey] + fDt*(m_akC[iKey]*((float)2.0) +
        m_akD[iKey]*(((float)3.0)*fDt));

    return kResult;
}
//----------------------------------------------------------------------------

Vector2 TCBSpline2::GetSecondDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector2 kResult = m_akC[iKey]*((float)2.0) +
        m_akD[iKey]*(((float)6.0)*fDt);

    return kResult;
}
//----------------------------------------------------------------------------

Vector2 TCBSpline2::GetThirdDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector2 kResult = ((float)6.0)*m_akD[iKey];

    return kResult;
}
//----------------------------------------------------------------------------

float TCBSpline2::GetSpeedKey (int iKey, float fTime) const
{
    Vector2 kVelocity = m_akB[iKey] + fTime*(m_akC[iKey]*((float)2.0) +
        m_akD[iKey]*(((float)3.0)*fTime));
    return kVelocity.Length();
}
//----------------------------------------------------------------------------

float TCBSpline2::GetLengthKey (int iKey, float fT0, float fT1) const
{
    ThisPlusKey kData(this,iKey);
    
	//return Integrate1::RombergIntegral(8,fT0,fT1,GetSpeedWithData, (void*)&kData);
	assert(0);
	return 0;
}
//----------------------------------------------------------------------------

float TCBSpline2::GetVariationKey (int iKey, float fT0, float fT1,
    const Vector2& rkA, const Vector2& rkB) const
{
    Polynomial1 kXPoly(3);
    kXPoly[0] = m_akA[iKey].X();
    kXPoly[1] = m_akB[iKey].X();
    kXPoly[2] = m_akC[iKey].X();
    kXPoly[3] = m_akD[iKey].X();

    Polynomial1 kYPoly(3);
    kYPoly[0] = m_akA[iKey].Y();
    kYPoly[1] = m_akB[iKey].Y();
    kYPoly[2] = m_akC[iKey].Y();
    kYPoly[3] = m_akD[iKey].Y();

    // construct line segment A + t*B
    Polynomial1 kLx(1), kLy(1);
    kLx[0] = rkA.X();
    kLx[1] = rkB.X();
    kLy[0] = rkA.Y();
    kLy[1] = rkB.Y();

    // compute |X(t) - L(t)|^2
    Polynomial1 kDx = kXPoly - kLx;
    Polynomial1 kDy = kYPoly - kLy;
    Polynomial1 kNormSqr = kDx*kDx + kDy*kDy;

    // compute indefinite integral of |X(t)-L(t)|^2
    Polynomial1 kIntegral(kNormSqr.GetDegree()+1);
    kIntegral[0] = (float)0.0;
    for (int i = 1; i <= kIntegral.GetDegree(); i++)
    {
        kIntegral[i] = kNormSqr[i-1]/i;
    }

    // compute definite Integral(t0,t1,|X(t)-L(t)|^2)
    float fResult = kIntegral(fT1) - kIntegral(fT0);
    return fResult;
}
//----------------------------------------------------------------------------

}

