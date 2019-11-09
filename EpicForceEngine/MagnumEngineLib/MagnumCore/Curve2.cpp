#include "Curve2.h"

namespace Magnum
{
//----------------------------------------------------------------------------

Curve2::Curve2 (float fTMin, float fTMax)
{
    m_fTMin = fTMin;
    m_fTMax = fTMax;
}
//----------------------------------------------------------------------------

Curve2::~Curve2 ()
{
}
//----------------------------------------------------------------------------

float Curve2::GetMinTime () const
{
    return m_fTMin;
}
//----------------------------------------------------------------------------

float Curve2::GetMaxTime () const
{
    return m_fTMax;
}
//----------------------------------------------------------------------------

void Curve2::SetTimeInterval (float fTMin, float fTMax)
{
    assert(fTMin < fTMax);
    m_fTMin = fTMin;
    m_fTMax = fTMax;
}
//----------------------------------------------------------------------------

float Curve2::GetSpeed (float fTime) const
{
    Vector2 kVelocity = GetFirstDerivative(fTime);
    float fSpeed = kVelocity.Length();
    return fSpeed;
}
//----------------------------------------------------------------------------

float Curve2::GetTotalLength () const
{
    return GetLength(m_fTMin,m_fTMax);
}
//----------------------------------------------------------------------------

Vector2 Curve2::GetTangent (float fTime) const
{
    Vector2 kVelocity = GetFirstDerivative(fTime);
    kVelocity.Normalize();
    return kVelocity;
}
//----------------------------------------------------------------------------

Vector2 Curve2::GetNormal (float fTime) const
{
    Vector2 kTangent = GetFirstDerivative(fTime);
    kTangent.Normalize();
    Vector2 kNormal = kTangent.Perp();
    return kNormal;
}
//----------------------------------------------------------------------------

void Curve2::GetFrame (float fTime, Vector2& rkPosition,
    Vector2& rkTangent, Vector2& rkNormal) const
{
    rkPosition = GetPosition(fTime);
    rkTangent = GetFirstDerivative(fTime);
    rkTangent.Normalize();
    rkNormal = rkTangent.Perp();
}
//----------------------------------------------------------------------------

float Curve2::GetCurvature (float fTime) const
{
    Vector2 kDer1 = GetFirstDerivative(fTime);
    Vector2 kDer2 = GetSecondDerivative(fTime);
    float fSpeedSqr = kDer1.SquaredLength();

    if (fSpeedSqr >= Math::ZERO_TOLERANCE)
    {
        float fNumer = kDer1.DotPerp(kDer2);
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

void Curve2::SubdivideByTime (int iNumPoints,
    Vector2*& rakPoint) const
{
    assert(iNumPoints >= 2);
    rakPoint = new Vector2[iNumPoints];

    float fDelta = (m_fTMax - m_fTMin)/(iNumPoints-1);

    for (int i = 0; i < iNumPoints; i++)
    {
        float fTime = m_fTMin + fDelta*i;
        rakPoint[i] = GetPosition(fTime);
    }
}
//----------------------------------------------------------------------------

void Curve2::SubdivideByLength (int iNumPoints,
    Vector2*& rakPoint) const
{
    assert(iNumPoints >= 2);
    rakPoint = new Vector2[iNumPoints];

    float fDelta = GetTotalLength()/(iNumPoints-1);

    for (int i = 0; i < iNumPoints; i++)
    {
        float fLength = fDelta*i;
        float fTime = GetTime(fLength);
        rakPoint[i] = GetPosition(fTime);
    }
}
//----------------------------------------------------------------------------

void Curve2::SubdivideByVariation (float fT0, const Vector2& rkP0,
    float fT1, const Vector2& rkP1, float fMinVariation,
    int iLevel, int& riNumPoints, PointList*& rpkList) const
{
    if (iLevel > 0 && GetVariation(fT0,fT1,&rkP0,&rkP1) > fMinVariation)
    {
        // too much variation, subdivide interval
        iLevel--;
        float fTMid = ((float)0.5)*(fT0+fT1);
        Vector2 kPMid = GetPosition(fTMid);

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

void Curve2::SubdivideByVariation (float fMinVariation, int iMaxLevel,
    int& riNumPoints, Vector2*& rakPoint) const
{
    // compute end points of curve
    Vector2 kPMin = GetPosition(m_fTMin);
    Vector2 kPMax = GetPosition(m_fTMax);

    // add left end point to list
    PointList* pkList = new PointList(kPMin,0);
    riNumPoints = 1;

    // binary subdivision, leaf nodes add right end point of subinterval
    SubdivideByVariation(m_fTMin,kPMin,m_fTMax,kPMax,fMinVariation,
        iMaxLevel,riNumPoints,pkList->m_kNext);

    // repackage points in an array
    assert(riNumPoints >= 2);
    rakPoint = new Vector2[riNumPoints];
    for (int i = 0; i < riNumPoints; i++)
    {
        assert(pkList);
        rakPoint[i] = pkList->m_kPoint;

        PointList* pkSave = pkList;
        pkList = pkList->m_kNext;
        delete pkSave;
    }
    assert(pkList == 0);
}
//----------------------------------------------------------------------------

}

