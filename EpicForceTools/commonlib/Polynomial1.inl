///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Polynomial1::Polynomial1 (int iDegree)
{
    if (iDegree >= 0)
    {
        m_iDegree = iDegree;
        m_afCoeff = new float[m_iDegree+1];
    }
    else
    {
        // default creation
        m_iDegree = -1;
        m_afCoeff = 0;
    }
}
//----------------------------------------------------------------------------
inline Polynomial1::Polynomial1 (const Polynomial1& rkPoly)
{
    m_iDegree = rkPoly.m_iDegree;
    m_afCoeff = new float[m_iDegree+1];
    for (int i = 0; i <= m_iDegree; i++)
    {
        m_afCoeff[i] = rkPoly.m_afCoeff[i];
    }
}
//----------------------------------------------------------------------------
inline Polynomial1::~Polynomial1 ()
{
    delete[] m_afCoeff;
}
//----------------------------------------------------------------------------
inline void Polynomial1::SetDegree (int iDegree)
{
    m_iDegree = iDegree;
    delete[] m_afCoeff;

    if (m_iDegree >= 0)
    {
        m_afCoeff = new float[m_iDegree+1];
    }
    else
    {
        m_afCoeff = 0;
    }
}
//----------------------------------------------------------------------------
inline int Polynomial1::GetDegree () const
{
    return m_iDegree;
}
//----------------------------------------------------------------------------
inline Polynomial1::operator const float* () const
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline Polynomial1::operator float* ()
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline float Polynomial1::operator[] (int i) const
{
    assert(0 <= i && i <= m_iDegree);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline float& Polynomial1::operator[] (int i)
{
    assert(0 <= i && i <= m_iDegree);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator= (const Polynomial1& rkPoly)
{
    delete[] m_afCoeff;
    m_iDegree = rkPoly.m_iDegree;

    if (m_iDegree >= 0)
    {
        m_afCoeff = new float[m_iDegree+1];
        for (int i = 0; i <= m_iDegree; i++)
        {
            m_afCoeff[i] = rkPoly.m_afCoeff[i];
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
inline float Polynomial1::operator() (float fT) const
{
    assert(m_iDegree >= 0);

    float fResult = m_afCoeff[m_iDegree];
    for (int i = m_iDegree-1; i >= 0; i--)
    {
        fResult *= fT;
        fResult += m_afCoeff[i];
    }
    return fResult;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator+ (const Polynomial1& rkPoly)
    const
{
    assert(m_iDegree >= 0 && rkPoly.m_iDegree >= 0);

    Polynomial1 kSum;
    int i;

    if (m_iDegree > rkPoly.m_iDegree)
    {
        kSum.SetDegree(m_iDegree);
        for (i = 0; i <= rkPoly.m_iDegree; i++)
        {
            kSum.m_afCoeff[i] = m_afCoeff[i] + rkPoly.m_afCoeff[i];
        }
        for (i = rkPoly.m_iDegree+1; i <= m_iDegree; i++)
        {
            kSum.m_afCoeff[i] = m_afCoeff[i];
        }

    }
    else
    {
        kSum.SetDegree(rkPoly.m_iDegree);
        for (i = 0; i <= m_iDegree; i++)
        {
            kSum.m_afCoeff[i] = m_afCoeff[i] + rkPoly.m_afCoeff[i];
        }
        for (i = m_iDegree+1; i <= rkPoly.m_iDegree; i++)
        {
            kSum.m_afCoeff[i] = rkPoly.m_afCoeff[i];
        }
    }

    return kSum;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator- (const Polynomial1& rkPoly)
    const
{
    assert(m_iDegree >= 0 && rkPoly.m_iDegree >= 0);

    Polynomial1 kDiff;
    int i;

    if (m_iDegree > rkPoly.m_iDegree)
    {
        kDiff.SetDegree(m_iDegree);
        for (i = 0; i <= rkPoly.m_iDegree; i++)
        {
            kDiff.m_afCoeff[i] = m_afCoeff[i] - rkPoly.m_afCoeff[i];
        }
        for (i = rkPoly.m_iDegree+1; i <= m_iDegree; i++)
        {
            kDiff.m_afCoeff[i] = m_afCoeff[i];
        }

    }
    else
    {
        kDiff.SetDegree(rkPoly.m_iDegree);
        for (i = 0; i <= m_iDegree; i++)
        {
            kDiff.m_afCoeff[i] = m_afCoeff[i] - rkPoly.m_afCoeff[i];
        }
        for (i = m_iDegree+1; i <= rkPoly.m_iDegree; i++)
        {
            kDiff.m_afCoeff[i] = -rkPoly.m_afCoeff[i];
        }
    }

    return kDiff;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator* (const Polynomial1& rkPoly)
    const
{
    assert(m_iDegree >= 0 && rkPoly.m_iDegree >= 0);

    Polynomial1 kProd(m_iDegree + rkPoly.m_iDegree);

    memset(kProd.m_afCoeff,0,(kProd.m_iDegree+1)*sizeof(float));
    for (int i0 = 0; i0 <= m_iDegree; i0++)
    {
        for (int i1 = 0; i1 <= rkPoly.m_iDegree; i1++)
        {
            int i2 = i0 + i1;
            kProd.m_afCoeff[i2] += m_afCoeff[i0]*rkPoly.m_afCoeff[i1];
        }
    }

    return kProd;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator+ (float fScalar) const
{
    assert(m_iDegree >= 0);
    Polynomial1 kSum(m_iDegree);
    kSum.m_afCoeff[0] += fScalar;
    return kSum;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator- (float fScalar) const
{
    assert(m_iDegree >= 0);
    Polynomial1 kDiff(m_iDegree);
    kDiff.m_afCoeff[0] -= fScalar;
    return kDiff;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator* (float fScalar) const
{
    assert(m_iDegree >= 0);

    Polynomial1 kProd(m_iDegree);
    for (int i = 0; i <= m_iDegree; i++)
    {
        kProd.m_afCoeff[i] = fScalar*m_afCoeff[i];
    }

    return kProd;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator/ (float fScalar) const
{
    assert(m_iDegree >= 0);

    Polynomial1 kProd(m_iDegree);
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i <= m_iDegree; i++)
        {
            kProd.m_afCoeff[i] = fInvScalar*m_afCoeff[i];
        }
    }
    else
    {
        for (i = 0; i <= m_iDegree; i++)
        {
            kProd.m_afCoeff[i] = Math::MAX_REAL;
        }
    }

    return kProd;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::operator- () const
{
    assert(m_iDegree >= 0);

    Polynomial1 kNeg(m_iDegree);
    for (int i = 0; i <= m_iDegree; i++)
    {
        kNeg.m_afCoeff[i] = -m_afCoeff[i];
    }

    return kNeg;
}
//----------------------------------------------------------------------------
inline Polynomial1 operator* (float fScalar,
    const Polynomial1& rkPoly)
{
    assert(rkPoly.GetDegree() >= 0);

    Polynomial1 kProd(rkPoly.GetDegree());
    for (int i = 0; i <= rkPoly.GetDegree(); i++)
    {
        kProd[i] = fScalar*rkPoly[i];
    }

    return kProd;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator += (const Polynomial1& rkPoly)
{
    assert(m_iDegree >= 0);
    *this = *this + rkPoly;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator -= (const Polynomial1& rkPoly)
{
    assert(m_iDegree >= 0);
    *this = *this - rkPoly;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator *= (const Polynomial1& rkPoly)
{
    assert(m_iDegree >= 0);
    *this = (*this)*rkPoly;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator += (float fScalar)
{
    assert(m_iDegree >= 0);
    m_afCoeff[0] += fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator -= (float fScalar)
{
    assert(m_iDegree >= 0);
    m_afCoeff[0] -= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator *= (float fScalar)
{
    assert(m_iDegree >= 0);
    *this = (*this)*fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1& Polynomial1::operator /= (float fScalar)
{
    assert(m_iDegree >= 0);
    *this = (*this)/fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::GetDerivative () const
{
    if (m_iDegree > 0)
    {
        Polynomial1 kDeriv(m_iDegree-1);
        for (int i0 = 0, i1 = 1; i0 < m_iDegree; i0++, i1++)
        {
            kDeriv.m_afCoeff[i0] = i1*m_afCoeff[i1];
        }
        return kDeriv;
    }
    else if (m_iDegree == 0)
    {
        Polynomial1 kConst(0);
        kConst.m_afCoeff[0] = (float)0.0;
        return kConst;
    }
    return Polynomial1();  // invalid in, invalid out
}
//----------------------------------------------------------------------------
inline Polynomial1 Polynomial1::GetInversion () const
{
    Polynomial1 kInvPoly(m_iDegree);
    for (int i = 0; i <= m_iDegree; i++)
    {
        kInvPoly.m_afCoeff[i] = m_afCoeff[m_iDegree-i];
    }
    return kInvPoly;
}
//----------------------------------------------------------------------------
inline void Polynomial1::Compress (float fEpsilon)
{
    int i;
    for (i = m_iDegree; i >= 0; i--)
    {
        if (Math::FAbs(m_afCoeff[i]) <= fEpsilon)
        {
            m_iDegree--;
        }
        else
        {
            break;
        }
    }

    if (m_iDegree >= 0)
    {
        float fInvLeading = ((float)1.0)/m_afCoeff[m_iDegree];
        m_afCoeff[m_iDegree] = (float)1.0;
        for (i = 0; i < m_iDegree; i++)
        {
            m_afCoeff[i] *= fInvLeading;
        }
    }
}
//----------------------------------------------------------------------------
inline void Polynomial1::Divide (const Polynomial1& rkDiv, Polynomial1& rkQuot,
    Polynomial1& rkRem, float fEpsilon) const
{
    int iQuotDegree = m_iDegree - rkDiv.m_iDegree;
    if (iQuotDegree >= 0)
    {
        rkQuot.SetDegree(iQuotDegree);

        // temporary storage for the remainder
        Polynomial1 kTmp = *this;

        // do the division (Euclidean algorithm)
        float fInv = ((float)1.0)/rkDiv[rkDiv.m_iDegree];
        for (int iQ = iQuotDegree; iQ >= 0; iQ--)
        {
            int iR = rkDiv.m_iDegree + iQ;
            rkQuot[iQ] = fInv*kTmp[iR];
            for (iR--; iR >= iQ; iR--)
            {
                kTmp[iR] -= rkQuot[iQ]*rkDiv[iR-iQ];
            }
        }

        // calculate the correct degree for the remainder
        int iRemDeg = rkDiv.m_iDegree - 1;
        while (iRemDeg > 0 && Math::FAbs(kTmp[iRemDeg]) < fEpsilon)
        {
            iRemDeg--;
        }

        if (iRemDeg == 0 && Math::FAbs(kTmp[0]) < fEpsilon)
        {
            kTmp[0] = (float)0.0;
        }

        rkRem.SetDegree(iRemDeg);
        size_t uiSize = (iRemDeg+1)*sizeof(float);
        memcpy(rkRem.m_afCoeff,kTmp.m_afCoeff,uiSize);
    }
    else
    {
        rkQuot.SetDegree(0);
        rkQuot[0] = (float)0.0;
        rkRem = *this;
    }
}
//----------------------------------------------------------------------------

