#include "Curve3.h"

namespace Magnum
{
//----------------------------------------------------------------------------

Curve3::Curve3 (float fTMin, float fTMax)
{
    m_fTMin = fTMin;
    m_fTMax = fTMax;
}
//----------------------------------------------------------------------------

Curve3::~Curve3 ()
{
}
//----------------------------------------------------------------------------

float Curve3::GetMinTime () const
{
    return m_fTMin;
}
//----------------------------------------------------------------------------

float Curve3::GetMaxTime () const
{
    return m_fTMax;
}
//----------------------------------------------------------------------------

void Curve3::SetTimeInterval (float fTMin, float fTMax)
{
    assert(fTMin < fTMax);
    m_fTMin = fTMin;
    m_fTMax = fTMax;
}
//----------------------------------------------------------------------------

float Curve3::GetSpeed (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    float fSpeed = kVelocity.Length();
    return fSpeed;
}
//----------------------------------------------------------------------------

float Curve3::GetTotalLength () const
{
    return GetLength(m_fTMin,m_fTMax);
}
//----------------------------------------------------------------------------

Vector3 Curve3::GetTangent (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    kVelocity.Normalize();
    return kVelocity;
}
//----------------------------------------------------------------------------

Vector3 Curve3::GetNormal (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    Vector3 kAcceleration = GetSecondDerivative(fTime);
    float fVDotV = kVelocity.Dot(kVelocity);
    float fVDotA = kVelocity.Dot(kAcceleration);
    Vector3 kNormal = fVDotV*kAcceleration - fVDotA*kVelocity;
    kNormal.Normalize();
    return kNormal;
}
//----------------------------------------------------------------------------

Vector3 Curve3::GetBinormal (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    Vector3 kAcceleration = GetSecondDerivative(fTime);
    float fVDotV = kVelocity.Dot(kVelocity);
    float fVDotA = kVelocity.Dot(kAcceleration);
    Vector3 kNormal = fVDotV*kAcceleration - fVDotA*kVelocity;
    kNormal.Normalize();
    kVelocity.Normalize();
    Vector3 kBinormal = kVelocity.Cross(kNormal);
    return kBinormal;
}
//----------------------------------------------------------------------------

void Curve3::GetFrame (float fTime, Vector3& rkPosition,
    Vector3& rkTangent, Vector3& rkNormal,
    Vector3& rkBinormal) const
{
    rkPosition = GetPosition(fTime);
    Vector3 kVelocity = GetFirstDerivative(fTime);
    Vector3 kAcceleration = GetSecondDerivative(fTime);
    float fVDotV = kVelocity.Dot(kVelocity);
    float fVDotA = kVelocity.Dot(kAcceleration);
    rkNormal = fVDotV*kAcceleration - fVDotA*kVelocity;
    rkNormal.Normalize();
    rkTangent = kVelocity;
    rkTangent.Normalize();
    rkBinormal = rkTangent.Cross(rkNormal);
}
//----------------------------------------------------------------------------

float Curve3::GetCurvature (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    float fSpeedSqr = kVelocity.SquaredLength();

    if (fSpeedSqr >= Math::ZERO_TOLERANCE)
    {
        Vector3 kAcceleration = GetSecondDerivative(fTime);
        Vector3 kCross = kVelocity.Cross(kAcceleration);
        float fNumer = kCross.Length();
        float fDenom = Math::Pow(fSpeedSqr,(float)1.5);
        return fNumer/fDenom;
    }
    else
    {
        // curvature is indeterminate, just return 0
        return (float)0.0;
    }
}
//----------------------------------------------------------------------------

float Curve3::GetTorsion (float fTime) const
{
    Vector3 kVelocity = GetFirstDerivative(fTime);
    Vector3 kAcceleration = GetSecondDerivative(fTime);
    Vector3 kCross = kVelocity.Cross(kAcceleration);
    float fDenom = kCross.SquaredLength();

    if (fDenom >= Math::ZERO_TOLERANCE)
    {
        Vector3 kJerk = GetThirdDerivative(fTime);
        float fNumer = kCross.Dot(kJerk);
        return fNumer/fDenom;
    }
    else
    {
        // torsion is indeterminate, just return 0
        return (float)0.0;
    }
}
//----------------------------------------------------------------------------

void Curve3::SubdivideByTime (int iNumPoints,
    Vector3*& rakPoint) const
{
    assert(iNumPoints >= 2);
    rakPoint = new Vector3[iNumPoints];

    float fDelta = (m_fTMax - m_fTMin)/(iNumPoints-1);

    for (int i = 0; i < iNumPoints; i++)
    {
        float fTime = m_fTMin + fDelta*i;
        rakPoint[i] = GetPosition(fTime);
    }
}
//----------------------------------------------------------------------------

void Curve3::SubdivideByLength (int iNumPoints,
    Vector3*& rakPoint) const
{
    assert(iNumPoints >= 2);
    rakPoint = new Vector3[iNumPoints];

    float fDelta = GetTotalLength()/(iNumPoints-1);

    for (int i = 0; i < iNumPoints; i++)
    {
        float fLength = fDelta*i;
        float fTime = GetTime(fLength);
        rakPoint[i] = GetPosition(fTime);
    }
}
//----------------------------------------------------------------------------

void Curve3::SubdivideByVariation (float fT0, const Vector3& rkP0,
    float fT1, const Vector3& rkP1, float fMinVariation, int iLevel,
    int& riNumPoints, PointList*& rpkList) const
{
    if (iLevel > 0 && GetVariation(fT0,fT1,&rkP0,&rkP1) > fMinVariation)
    {
        // too much variation, subdivide interval
        iLevel--;
        float fTMid = ((float)0.5)*(fT0+fT1);
        Vector3 kPMid = GetPosition(fTMid);

        SubdivideByVariation(fT0,rkP0,fTMid,kPMid,fMinVariation,iLevel,
            riNumPoints,rpkList);

        SubdivideByVariation(fTMid,kPMid,fT1,rkP1,fMinVariation,iLevel,
            riNumPoints,rpkList);
    }
    else
    {
        // add right end point, left end point was added by neighbor
        rpkList = new PointList(rkP1,rpkList);
        riNumPoints++;
    }
}
//----------------------------------------------------------------------------

void Curve3::SubdivideByVariation (float fMinVariation, int iMaxLevel,
    int& riNumPoints, Vector3*& rakPoint) const
{
    // compute end points of curve
    Vector3 kPMin = GetPosition(m_fTMin);
    Vector3 kPMax = GetPosition(m_fTMax);

    // add left end point to list
    PointList* pkList = new PointList(kPMin,0);
    riNumPoints = 1;

    // binary subdivision, leaf nodes add right end point of subinterval
    SubdivideByVariation(m_fTMin,kPMin,m_fTMax,kPMax,fMinVariation,
        iMaxLevel,riNumPoints,pkList->m_kNext);

    // repackage points in an array
    assert(riNumPoints >= 2);
    rakPoint = new Vector3[riNumPoints];
    for (int i = 0; i < riNumPoints; i++)
    {
        assert( pkList );
        rakPoint[i] = pkList->m_kPoint;

        PointList* pkSave = pkList;
        pkList = pkList->m_kNext;
        delete pkSave;
    }
    assert(pkList == 0);
}
//----------------------------------------------------------------------------

}

