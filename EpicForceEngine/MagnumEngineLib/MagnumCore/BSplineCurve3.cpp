///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BSplineCurve3.h"

namespace Magnum
{
//----------------------------------------------------------------------------

BSplineCurve3::BSplineCurve3 (int iNumCtrlPoints,
    const Vector3* akCtrlPoint, int iDegree, bool bLoop, bool bOpen)
    :
    SingleCurve3((float)0.0,(float)1.0),
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

BSplineCurve3::BSplineCurve3 (int iNumCtrlPoints,
    const Vector3* akCtrlPoint, int iDegree, bool bLoop,
    const float* afKnot)
    :
    SingleCurve3((float)0.0,(float)1.0),
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

BSplineCurve3::~BSplineCurve3 ()
{
    delete[] m_akCtrlPoint;
}
//----------------------------------------------------------------------------

void BSplineCurve3::CreateControl (const Vector3* akCtrlPoint)
{
    int iNewNumCtrlPoints = m_iNumCtrlPoints + m_iReplicate;
    m_akCtrlPoint = new Vector3[iNewNumCtrlPoints];
    size_t uiDstSize = iNewNumCtrlPoints*sizeof(Vector3);
    size_t uiSrcSize = m_iNumCtrlPoints*sizeof(Vector3);
    memcpy(m_akCtrlPoint,akCtrlPoint,uiSrcSize);
    for (int i = 0; i < m_iReplicate; i++)
    {
        m_akCtrlPoint[m_iNumCtrlPoints+i] = akCtrlPoint[i];
    }
}
//----------------------------------------------------------------------------

int BSplineCurve3::GetNumCtrlPoints () const
{
    return m_iNumCtrlPoints;
}
//----------------------------------------------------------------------------

int BSplineCurve3::GetDegree () const
{
    return m_kBasis.GetDegree();
}
//----------------------------------------------------------------------------

bool BSplineCurve3::IsOpen () const
{
    return m_kBasis.IsOpen();
}
//----------------------------------------------------------------------------

bool BSplineCurve3::IsUniform () const
{
    return m_kBasis.IsUniform();
}
//----------------------------------------------------------------------------

bool BSplineCurve3::IsLoop () const
{
    return m_bLoop;
}
//----------------------------------------------------------------------------

void BSplineCurve3::SetControlPoint (int i, const Vector3& rkCtrl)
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

Vector3 BSplineCurve3::GetControlPoint (int i) const
{
    if (0 <= i && i < m_iNumCtrlPoints)
    {
        return m_akCtrlPoint[i];
    }

    return Vector3(Math::MAX_REAL,Math::MAX_REAL,
        Math::MAX_REAL);
}
//----------------------------------------------------------------------------

void BSplineCurve3::SetKnot (int i, float fKnot)
{
    m_kBasis.SetKnot(i,fKnot);
}
//----------------------------------------------------------------------------

float BSplineCurve3::GetKnot (int i) const
{
    return m_kBasis.GetKnot(i);
}
//----------------------------------------------------------------------------

void BSplineCurve3::Get (float fTime, Vector3* pkPos,
    Vector3* pkDer1, Vector3* pkDer2, Vector3* pkDer3) const
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
        *pkPos = Vector3::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkPos += m_kBasis.GetD0(i)*m_akCtrlPoint[i];
        }
    }

    if (pkDer1)
    {
        *pkDer1 = Vector3::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer1 += m_kBasis.GetD1(i)*m_akCtrlPoint[i];
        }
    }

    if (pkDer2)
    {
        *pkDer2 = Vector3::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer2 += m_kBasis.GetD2(i)*m_akCtrlPoint[i];
        }
    }

    if (pkDer3)
    {
        *pkDer3 = Vector3::ZERO;
        for (i = iMin; i <= iMax; i++)
        {
            *pkDer3 += m_kBasis.GetD3(i)*m_akCtrlPoint[i];
        }
    }
}
//----------------------------------------------------------------------------

BSplineBasis& BSplineCurve3::GetBasis ()
{
    return m_kBasis;
}
//----------------------------------------------------------------------------

Vector3 BSplineCurve3::GetPosition (float fTime) const
{
    Vector3 kPos;
    Get(fTime,&kPos,0,0,0);
    return kPos;
}
//----------------------------------------------------------------------------

Vector3 BSplineCurve3::GetFirstDerivative (float fTime) const
{
    Vector3 kDer1;
    Get(fTime,0,&kDer1,0,0);
    return kDer1;
}
//----------------------------------------------------------------------------

Vector3 BSplineCurve3::GetSecondDerivative (float fTime) const
{
    Vector3 kDer2;
    Get(fTime,0,0,&kDer2,0);
    return kDer2;
}
//----------------------------------------------------------------------------

Vector3 BSplineCurve3::GetThirdDerivative (float fTime) const
{
    Vector3 kDer3;
    Get(fTime,0,0,0,&kDer3);
    return kDer3;
}
//----------------------------------------------------------------------------

float BSplineCurve3::GetVariation (float, float, const Vector3*,
    const Vector3*) const
{
    return (float)0.0;
}
//----------------------------------------------------------------------------

}

