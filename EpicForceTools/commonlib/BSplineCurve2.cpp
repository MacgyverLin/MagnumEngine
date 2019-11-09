///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "BSplineCurve2.h"

namespace EpicForce
{
//----------------------------------------------------------------------------

BSplineCurve2::BSplineCurve2 (int iNumCtrlPoints,
    const Vector2* akCtrlPoint, int iDegree, bool bLoop, bool bOpen)
    :
    SingleCurve2((float)0.0,(float)1.0),
    m_bLoop(bLoop)
{
    assert(iNumCtrlPoints >= 2);
    assert(1 <= iDegree && iDegree <= iNumCtrlPoints-1);

    m_iNumCtrlPoints = iNumCtrlPoints;
    m_iReplicate = (bLoop ? (bOpen ? 1 : iDegree) : 0);
    CreateControl(akCtrlPoint);
    m_kBasis.Create(m_iNumCtrlPoints+m_iReplicate,iDegree,bOpen);
}
//----------------------------------------------------------------------------

BSplineCurve2::BSplineCurve2 (int iNumCtrlPoints,
    const Vector2* akCtrlPoint, int iDegree, bool bLoop,
    const float* afKnot)
    :
    SingleCurve2((float)0.0,(float)1.0),
    m_bLoop(bLoop)
{
    assert(iNumCtrlPoints >= 2);
    assert(1 <= iDegree && iDegree <= iNumCtrlPoints-1);

    m_iNumCtrlPoints = iNumCtrlPoints;
    m_iReplicate = (bLoop ? 1 : 0);
    CreateControl(akCtrlPoint);
    m_kBasis.Create(m_iNumCtrlPoints+m_iReplicate,iDegree,afKnot);
}
//----------------------------------------------------------------------------

BSplineCurve2::~BSplineCurve2 ()
{
    delete[] m_akCtrlPoint;
}
//----------------------------------------------------------------------------

void BSplineCurve2::CreateControl (const Vector2* akCtrlPoint)
{
    int iNewNumCtrlPoints = m_iNumCtrlPoints + m_iReplicate;
    m_akCtrlPoint = new Vector2[iNewNumCtrlPoints];
    size_t uiDstSize = iNewNumCtrlPoints*sizeof(Vector2);
    size_t uiSrcSize = m_iNumCtrlPoints*sizeof(Vector2);
    memcpy(m_akCtrlPoint,akCtrlPoint,uiSrcSize);
    for (int i = 0; i < m_iReplicate; i++)
    {
        m_akCtrlPoint[m_iNumCtrlPoints+i] = akCtrlPoint[i];
    }
}
//----------------------------------------------------------------------------

int BSplineCurve2::GetNumCtrlPoints () const
{
    return m_iNumCtrlPoints;
}
//----------------------------------------------------------------------------

int BSplineCurve2::GetDegree () const
{
    return m_kBasis.GetDegree();
}
//----------------------------------------------------------------------------

bool BSplineCurve2::IsOpen () const
{
    return m_kBasis.IsOpen();
}
//----------------------------------------------------------------------------

bool BSplineCurve2::IsUniform () const
{
    return m_kBasis.IsUniform();
}
//----------------------------------------------------------------------------

bool BSplineCurve2::IsLoop () const
{
    return m_bLoop;
}
//----------------------------------------------------------------------------

void BSplineCurve2::SetControlPoint (int i, const Vector2& rkCtrl)
{
    if (0 <= i && i < m_iNumCtrlPoints)
    {
        // set the control point
        m_akCtrlPoint[i] = rkCtrl;

        // set the replicated control point
        if (i < m_iReplicate)
        {
            m_akCtrlPoint[m_iNumCtrlPoints+i] = rkCtrl;
        }
    }
}
//----------------------------------------------------------------------------

Vector2 BSplineCurve2::GetControlPoint (int i) const
{
    if (0 <= i && i < m_iNumCtrlPoints)
    {
        return m_akCtrlPoint[i];
    }

    return Vector2(Math::MAX_REAL,Math::MAX_REAL);
}
//----------------------------------------------------------------------------

void BSplineCurve2::SetKnot (int i, float fKnot)
{
    m_kBasis.SetKnot(i,fKnot);
}
//----------------------------------------------------------------------------

float BSplineCurve2::GetKnot (int i) const
{
    return m_kBasis.GetKnot(i);
}
//----------------------------------------------------------------------------

void BSplineCurve2::Get (float fTime, Vector2* pkPos,
    Vector2* pkDer1, Vector2* pkDer2, Vector2* pkDer3) const
{
    int i, iMin, iMax;
    if (pkDer3)
    {
        m_kBasis.Compute(fTime,3,iMin,iMax);
    }
    else if (pkDer2)
    {
        m_kBasis.Compute(fTime,2,iMin,iMax);
    }
    else if (pkDer1)
    {
        m_kBasis.Compute(fTime,1,iMin,iMax);
    }
    else
    {
        m_kBasis.Compute(fTime,0,iMin,iMax);
    }

    if (pkPos)
    {
        *pkPos = Vector2::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkPos += m_akCtrlPoint[i]*m_kBasis.GetD0(i);
        }
    }

    if (pkDer1)
    {
        *pkDer1 = Vector2::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer1 += m_akCtrlPoint[i]*m_kBasis.GetD1(i);
        }
    }

    if (pkDer2)
    {
        *pkDer2 = Vector2::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer2 += m_akCtrlPoint[i]*m_kBasis.GetD2(i);
        }
    }

    if (pkDer3)
    {
        *pkDer3 = Vector2::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer3 += m_akCtrlPoint[i]*m_kBasis.GetD3(i);
        }
    }
}
//----------------------------------------------------------------------------

BSplineBasis& BSplineCurve2::GetBasis ()
{
    return m_kBasis;
}
//----------------------------------------------------------------------------

Vector2 BSplineCurve2::GetPosition (float fTime) const
{
    Vector2 kPos;
    Get(fTime,&kPos,0,0,0);
    return kPos;
}
//----------------------------------------------------------------------------

Vector2 BSplineCurve2::GetFirstDerivative (float fTime) const
{
    Vector2 kDer1;
    Get(fTime,0,&kDer1,0,0);
    return kDer1;
}
//----------------------------------------------------------------------------

Vector2 BSplineCurve2::GetSecondDerivative (float fTime) const
{
    Vector2 kDer2;
    Get(fTime,0,0,&kDer2,0);
    return kDer2;
}
//----------------------------------------------------------------------------

Vector2 BSplineCurve2::GetThirdDerivative (float fTime) const
{
    Vector2 kDer3;
    Get(fTime,0,0,0,&kDer3);
    return kDer3;
}
//----------------------------------------------------------------------------

float BSplineCurve2::GetVariation (float, float, const Vector2*,
    const Vector2*) const
{
    // TO DO.
    return (float)0.0;
}
//----------------------------------------------------------------------------

}

