///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "TCBSpline3.h"
//#include "Integrate1.h"
#include "Polynomial1.h"

namespace Magnum
{
//----------------------------------------------------------------------------

TCBSpline3::TCBSpline3 (int iSegments, float* afTime,
    Vector3* akPoint, float* afTension, float* afContinuity, float* afBias)
    :
    MultipleCurve3(iSegments,afTime)
{
    // TO DO.  Add 'boundary type' just as in natural splines.
    assert(m_iSegments >= 3);

    // all four of these arrays have m_iSegments+1 elements
    m_akPoint = akPoint;
    m_afTension = afTension;
    m_afContinuity = afContinuity;
    m_afBias = afBias;

    m_akA = new Vector3[m_iSegments];
    m_akB = new Vector3[m_iSegments];
    m_akC = new Vector3[m_iSegments];
    m_akD = new Vector3[m_iSegments];

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

TCBSpline3::~TCBSpline3 ()
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

const Vector3* TCBSpline3::GetPoints () const
{
    return m_akPoint;
}
//----------------------------------------------------------------------------

const float* TCBSpline3::GetTensions () const
{
    return m_afTension;
}
//----------------------------------------------------------------------------

const float* TCBSpline3::GetContinuities () const
{
    return m_afContinuity;
}
//----------------------------------------------------------------------------

const float* TCBSpline3::GetBiases () const
{
    return m_afBias;
}
//----------------------------------------------------------------------------

void TCBSpline3::ComputePoly (int i0, int i1, int i2, int i3)
{
    Vector3 kDiff = m_akPoint[i2] - m_akPoint[i1];
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
    Vector3 kTOut = fOut1*kDiff + fOut0*(m_akPoint[i1] - m_akPoint[i0]);

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
    Vector3 kTIn = fIn1*(m_akPoint[i3] - m_akPoint[i2]) + fIn0*kDiff;

    m_akA[i1] = m_akPoint[i1];
    m_akB[i1] = kTOut;
    m_akC[i1] = ((float)3.0)*kDiff - ((float)2.0)*kTOut - kTIn;
    m_akD[i1] = ((float)-2.0)*kDiff + kTOut + kTIn;
}
//----------------------------------------------------------------------------

Vector3 TCBSpline3::GetPosition (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector3 kResult = m_akA[iKey] + fDt*(m_akB[iKey] + fDt*(m_akC[iKey]
        + fDt*m_akD[iKey]));

    return kResult;
}
//----------------------------------------------------------------------------

Vector3 TCBSpline3::GetFirstDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector3 kResult = m_akB[iKey] + fDt*(((float)2.0)*m_akC[iKey] +
        ((float)3.0)*fDt*m_akD[iKey]);

    return kResult;
}
//----------------------------------------------------------------------------

Vector3 TCBSpline3::GetSecondDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector3 kResult = ((float)2.0)*m_akC[iKey] +
        ((float)6.0)*fDt*m_akD[iKey];

    return kResult;
}
//----------------------------------------------------------------------------

Vector3 TCBSpline3::GetThirdDerivative (float fTime) const
{
    int iKey;
    float fDt;
    GetKeyInfo(fTime,iKey,fDt);

    fDt /= (m_afTime[iKey+1] - m_afTime[iKey]);

    Vector3 kResult = ((float)6.0)*m_akD[iKey];

    return kResult;
}
//----------------------------------------------------------------------------

float TCBSpline3::GetSpeedKey (int iKey, float fTime) const
{
    Vector3 kVelocity = m_akB[iKey] + fTime*(((float)2.0)*m_akC[iKey] +
        ((float)3.0)*fTime*m_akD[iKey]);
    return kVelocity.Length();
}
//----------------------------------------------------------------------------

float TCBSpline3::GetLengthKey (int iKey, float fT0, float fT1) const
{
    ThisPlusKey kData(this,iKey);
    
	//return Integrate1::RombergIntegral(8,fT0,fT1,GetSpeedWithData, (void*)&kData);
	assert(0);
	return 0;
}
//----------------------------------------------------------------------------

float TCBSpline3::GetVariationKey (int iKey, float fT0, float fT1,
    const Vector3& rkA, const Vector3& rkB) const
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

    Polynomial1 kZPoly(3);
    kZPoly[0] = m_akA[iKey].Z();
    kZPoly[1] = m_akB[iKey].Z();
    kZPoly[2] = m_akC[iKey].Z();
    kZPoly[3] = m_akD[iKey].Z();

    // construct line segment A + t*B
    Polynomial1 kLx(1), kLy(1), kLz(1);
    kLx[0] = rkA.X();
    kLx[1] = rkB.X();
    kLy[0] = rkA.Y();
    kLy[1] = rkB.Y();
    kLz[0] = rkA.Z();
    kLz[1] = rkB.Z();

    // compute |X(t) - L(t)|^2
    Polynomial1 kDx = kXPoly - kLx;
    Polynomial1 kDy = kYPoly - kLy;
    Polynomial1 kDz = kZPoly - kLz;
    Polynomial1 kNormSqr = kDx*kDx + kDy*kDy + kDz*kDz;

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

