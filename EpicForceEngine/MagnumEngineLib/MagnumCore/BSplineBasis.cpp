///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BSplineBasis.h"

namespace Magnum
{
//----------------------------------------------------------------------------

BSplineBasis::BSplineBasis ()
{
}
//----------------------------------------------------------------------------

BSplineBasis::BSplineBasis (int iNumCtrlPoints, int iDegree, bool bOpen)
{
    Create(iNumCtrlPoints,iDegree,bOpen);
}
//----------------------------------------------------------------------------

void BSplineBasis::Create (int iNumCtrlPoints, int iDegree, bool bOpen)
{
    m_bUniform = true;

    int i, iNumKnots = Initialize(iNumCtrlPoints,iDegree,bOpen);
    float fFactor = ((float)1.0)/(m_iNumCtrlPoints-m_iDegree);
    if (m_bOpen)
    {
        for (i = 0; i <= m_iDegree; i++)
        {
            m_afKnot[i] = (float)0.0;
        }

        for (/**/; i < m_iNumCtrlPoints; i++)
        {
            m_afKnot[i] = (i-m_iDegree)*fFactor;
        }

        for (/**/; i < iNumKnots; i++)
        {
            m_afKnot[i] = (float)1.0;
        }
    }
    else
    {
        for (i = 0; i < iNumKnots; i++)
        {
            m_afKnot[i] = (i-m_iDegree)*fFactor;
        }
    }
}
//----------------------------------------------------------------------------

BSplineBasis::BSplineBasis (int iNumCtrlPoints, int iDegree,
    const float* afKnot)
{
    Create(iNumCtrlPoints,iDegree,afKnot);
}
//----------------------------------------------------------------------------

void BSplineBasis::Create (int iNumCtrlPoints, int iDegree,
    const float* afKnot)
{
    m_bUniform = false;

    int i, iNumKnots = Initialize(iNumCtrlPoints,iDegree,true);
    for (i = 0; i <= m_iDegree; i++)
    {
        m_afKnot[i] = (float)0.0;
    }

    for (int j = 0; i < m_iNumCtrlPoints; i++, j++)
    {
        m_afKnot[i] = afKnot[j];
    }

    for (/**/; i < iNumKnots; i++)
    {
        m_afKnot[i] = (float)1.0;
    }
}
//----------------------------------------------------------------------------

BSplineBasis::~BSplineBasis ()
{
    delete[] m_afKnot;
    Deallocate(m_aafBD0);
    Deallocate(m_aafBD1);
    Deallocate(m_aafBD2);
    Deallocate(m_aafBD3);
}
//----------------------------------------------------------------------------

int BSplineBasis::GetNumCtrlPoints () const
{
    return m_iNumCtrlPoints;
}
//----------------------------------------------------------------------------

int BSplineBasis::GetDegree () const
{
    return m_iDegree;
}
//----------------------------------------------------------------------------

bool BSplineBasis::IsOpen () const
{
    return m_bOpen;
}
//----------------------------------------------------------------------------

bool BSplineBasis::IsUniform () const
{
    return m_bUniform;
}
//----------------------------------------------------------------------------

float BSplineBasis::GetD0 (int i) const
{
    return m_aafBD0[m_iDegree][i];
}
//----------------------------------------------------------------------------

float BSplineBasis::GetD1 (int i) const
{
    return m_aafBD1[m_iDegree][i];
}
//----------------------------------------------------------------------------

float BSplineBasis::GetD2 (int i) const
{
    return m_aafBD2[m_iDegree][i];
}
//----------------------------------------------------------------------------

float BSplineBasis::GetD3 (int i) const
{
    return m_aafBD3[m_iDegree][i];
}
//----------------------------------------------------------------------------

template <class T>
void Allocate (int iCols, int iRows, T**& raatArray)
{
    raatArray = new T*[iRows];
    raatArray[0] = new T[iRows*iCols];
    for (int iRow = 1; iRow < iRows; iRow++)
    {
        raatArray[iRow] = &raatArray[0][iCols*iRow];
    }
}
//----------------------------------------------------------------------------
template <class T>
void Deallocate (T**& raatArray)
{
    delete[] raatArray[0];
    delete[] raatArray;
    raatArray = 0;
}

float** BSplineBasis::Allocate () const
{
    int iRows = m_iDegree + 1;
    int iCols = m_iNumCtrlPoints + m_iDegree;
    float** aafArray;
    Magnum::Allocate(iCols,iRows,aafArray);
    memset(aafArray[0],0,iRows*iCols*sizeof(float));
    return aafArray;
}
//----------------------------------------------------------------------------

void BSplineBasis::Deallocate (float** aafArray)
{
    if (aafArray)
    {
        Deallocate(aafArray);
    }
}
//----------------------------------------------------------------------------

int BSplineBasis::Initialize (int iNumCtrlPoints, int iDegree,
    bool bOpen)
{
    assert(iNumCtrlPoints >= 2);
    assert(1 <= iDegree && iDegree <= iNumCtrlPoints-1);

    m_iNumCtrlPoints = iNumCtrlPoints;
    m_iDegree = iDegree;
    m_bOpen = bOpen;

    int iNumKnots = m_iNumCtrlPoints+m_iDegree+1;
    m_afKnot = new float[iNumKnots];

    m_aafBD0 = Allocate();
    m_aafBD1 = 0;
    m_aafBD2 = 0;
    m_aafBD3 = 0;

    return iNumKnots;
}
//----------------------------------------------------------------------------

void BSplineBasis::SetKnot (int i, float fKnot)
{
    if (!m_bUniform)
    {
        // access only allowed to elements d+1 <= j <= n
        int j = i + m_iDegree + 1;
        if (m_iDegree+1 <= j && j <= m_iNumCtrlPoints - 1)
        {
            m_afKnot[j] = fKnot;
        }
    }
}
//----------------------------------------------------------------------------

float BSplineBasis::GetKnot (int i) const
{
    if (!m_bUniform)
    {
        // access only allowed to elements d+1 <= j <= n
        int j = i + m_iDegree + 1;
        if (m_iDegree+1 <= j && j <= m_iNumCtrlPoints - 1)
        {
            return m_afKnot[j];
        }
    }

    return Math::MAX_REAL;
}
//----------------------------------------------------------------------------

int BSplineBasis::GetKey (float& rfTime) const
{
    if (m_bOpen)
    {
        // open splines clamp to [0,1]
        if (rfTime <= (float)0.0)
        {
            rfTime = (float)0.0;
            return m_iDegree;
        }
        else if (rfTime >= (float)1.0)
        {
            rfTime = (float)1.0;
            return m_iNumCtrlPoints-1;
        }
    }
    else
    {
        // periodic splines wrap to [0,1]
        if (rfTime < (float)0.0 || rfTime > (float)1.0)
        {
            rfTime -= Math::Floor(rfTime);
        }
    }


    int i;

    if (m_bUniform)
    {
        i = m_iDegree + (int)((m_iNumCtrlPoints-m_iDegree)*rfTime);
    }
    else
    {
        for (i = m_iDegree+1; i <= m_iNumCtrlPoints; i++)
        {
            if (rfTime < m_afKnot[i])
            {
                break;
            }
        }
        i--;
    }

    return i;
}
//----------------------------------------------------------------------------

void BSplineBasis::Compute (float fTime, unsigned int uiOrder,
    int& riMinIndex, int& riMaxIndex) const
{
    // only derivatives through third order currently supported
    assert(uiOrder <= 3);

    if (uiOrder >= 1)
    {
        if (!m_aafBD1)
        {
            m_aafBD1 = Allocate();
        }

        if (uiOrder >= 2)
        {
            if (!m_aafBD2)
            {
                m_aafBD2 = Allocate();
            }

            if (uiOrder >= 3)
            {
                if (!m_aafBD3)
                {
                    m_aafBD3 = Allocate();
                }
            }
        }
    }

    int i = GetKey(fTime);
    m_aafBD0[0][i] = (float)1.0;

    if (uiOrder >= 1)
    {
        m_aafBD1[0][i] = (float)0.0;
        if (uiOrder >= 2)
        {
            m_aafBD2[0][i] = (float)0.0;
            if (uiOrder >= 3)
            {
                m_aafBD3[0][i] = (float)0.0;
            }
        }
    }

    float fN0 = fTime-m_afKnot[i], fN1 = m_afKnot[i+1]-fTime;
    float fInvD0, fInvD1;
    int j;
    for (j = 1; j <= m_iDegree; j++)
    {
        fInvD0 = ((float)1.0)/(m_afKnot[i+j]-m_afKnot[i]);
        fInvD1 = ((float)1.0)/(m_afKnot[i+1]-m_afKnot[i-j+1]);

        m_aafBD0[j][i] = fN0*m_aafBD0[j-1][i]*fInvD0;
        m_aafBD0[j][i-j] = fN1*m_aafBD0[j-1][i-j+1]*fInvD1;

        if (uiOrder >= 1)
        {
            m_aafBD1[j][i] = (fN0*m_aafBD1[j-1][i]+m_aafBD0[j-1][i])*fInvD0;
            m_aafBD1[j][i-j] = (fN1*m_aafBD1[j-1][i-j+1]-m_aafBD0[j-1][i-j+1])
                *fInvD1;

            if (uiOrder >= 2)
            {
                m_aafBD2[j][i] = (fN0*m_aafBD2[j-1][i] +
                    ((float)2.0)*m_aafBD1[j-1][i])*fInvD0;
                m_aafBD2[j][i-j] = (fN1*m_aafBD2[j-1][i-j+1] -
                    ((float)2.0)*m_aafBD1[j-1][i-j+1])*fInvD1;

                if (uiOrder >= 3)
                {
                    m_aafBD3[j][i] = (fN0*m_aafBD3[j-1][i] +
                        ((float)3.0)*m_aafBD2[j-1][i])*fInvD0;
                    m_aafBD3[j][i-j] = (fN1*m_aafBD3[j-1][i-j+1] -
                        ((float)3.0)*m_aafBD2[j-1][i-j+1])*fInvD1;
                }
            }
        }
    }

    for (j = 2; j <= m_iDegree; j++)
    {
        for (int k = i-j+1; k < i; k++)
        {
            fN0 = fTime-m_afKnot[k];
            fN1 = m_afKnot[k+j+1]-fTime;
            fInvD0 = ((float)1.0)/(m_afKnot[k+j]-m_afKnot[k]);
            fInvD1 = ((float)1.0)/(m_afKnot[k+j+1]-m_afKnot[k+1]);

            m_aafBD0[j][k] = fN0*m_aafBD0[j-1][k]*fInvD0 + fN1*
                m_aafBD0[j-1][k+1]*fInvD1;

            if (uiOrder >= 1)
            {
                m_aafBD1[j][k] = (fN0*m_aafBD1[j-1][k]+m_aafBD0[j-1][k])*
                    fInvD0 + (fN1*m_aafBD1[j-1][k+1]-m_aafBD0[j-1][k+1])*
                    fInvD1;

                if (uiOrder >= 2)
                {
                    m_aafBD2[j][k] = (fN0*m_aafBD2[j-1][k] +
                        ((float)2.0)*m_aafBD1[j-1][k])*fInvD0 +
                        (fN1*m_aafBD2[j-1][k+1]- ((float)2.0)*
                        m_aafBD1[j-1][k+1])*fInvD1;

                    if (uiOrder >= 3)
                    {
                        m_aafBD3[j][k] = (fN0*m_aafBD3[j-1][k] +
                            ((float)3.0)*m_aafBD2[j-1][k])*fInvD0 +
                            (fN1*m_aafBD3[j-1][k+1] - ((float)3.0)*
                            m_aafBD2[j-1][k+1])*fInvD1;
                    }
                }
            }
        }
    }

    riMinIndex = i - m_iDegree;
    riMaxIndex = i;
}
//----------------------------------------------------------------------------

}

