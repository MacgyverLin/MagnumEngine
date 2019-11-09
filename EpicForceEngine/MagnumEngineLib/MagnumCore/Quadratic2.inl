///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Quadratic2::Quadratic2 ()
{
    memset(m_afCoeff,0,6*sizeof(float));
}
//----------------------------------------------------------------------------
inline Quadratic2::Quadratic2 (float fA0, float fA1, float fA2, float fA3,
    float fA4, float fA5)
{
    m_afCoeff[0] = fA0;
    m_afCoeff[1] = fA1;
    m_afCoeff[2] = fA2;
    m_afCoeff[3] = fA3;
    m_afCoeff[4] = fA4;
    m_afCoeff[5] = fA5;
}
//----------------------------------------------------------------------------
inline Quadratic2::Quadratic2 (const float afA[6])
{
    size_t uiSize = 6*sizeof(float);
    System::memcpy(m_afCoeff,afA,uiSize);
}
//----------------------------------------------------------------------------
inline Quadratic2::operator const float* () const
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline Quadratic2::operator float* ()
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline float Quadratic2::operator[] (int i) const
{
    assert(0 <= i && i < 6);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::operator[] (int i)
{
    assert(0 <= i && i < 6);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline float Quadratic2::Constant() const
{
    return m_afCoeff[0];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::Constant()
{
    return m_afCoeff[0];
}
//----------------------------------------------------------------------------
inline float Quadratic2::X() const
{
    return m_afCoeff[1];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::X()
{
    return m_afCoeff[1];
}
//----------------------------------------------------------------------------
inline float Quadratic2::Y() const
{
    return m_afCoeff[2];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::Y()
{
    return m_afCoeff[2];
}
//----------------------------------------------------------------------------
inline float Quadratic2::XX() const
{
    return m_afCoeff[3];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::XX()
{
    return m_afCoeff[3];
}
//----------------------------------------------------------------------------
inline float Quadratic2::XY() const
{
    return m_afCoeff[4];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::XY()
{
    return m_afCoeff[4];
}
//----------------------------------------------------------------------------
inline float Quadratic2::YY() const
{
    return m_afCoeff[5];
}
//----------------------------------------------------------------------------
inline float& Quadratic2::YY()
{
    return m_afCoeff[5];
}
//----------------------------------------------------------------------------
inline void Quadratic2::Set (int iXOrder, int iYOrder, float fCoeff)
{
    if (iXOrder >= 0 && iYOrder >= 0)
    {
        int iSum = iXOrder + iYOrder;
        if (iSum <= 2)
        {
            int i = iSum*(1+iSum)/2 + iYOrder;
            assert(0 <= i && i < 6);
            m_afCoeff[i] = fCoeff;
        }
    }
}
//----------------------------------------------------------------------------
inline float Quadratic2::Get (int iXOrder, int iYOrder) const
{
    if (iXOrder >= 0 && iYOrder >= 0)
    {
        int iSum = iXOrder + iYOrder;
        if (iSum <= 2)
        {
            int i = iSum*(1+iSum)/2 + iYOrder;
            assert(0 <= i && i < 6);
            return m_afCoeff[i];
        }
    }

    return (float)0.0;
}
//----------------------------------------------------------------------------
inline float Quadratic2::operator() (float fX, float fY) const
{
    float fResult = m_afCoeff[0] + fX*(m_afCoeff[1] + fX*m_afCoeff[3]) +
        fY*(m_afCoeff[2] + fX*m_afCoeff[4] + fY*m_afCoeff[5]);
    return fResult;
}
//----------------------------------------------------------------------------
inline float Quadratic2::operator() (const Vector2& rkP) const
{
    return (*this)(rkP.X(),rkP.Y());
}
//----------------------------------------------------------------------------
inline Quadratic2 Quadratic2::Translate (const Vector2& rkTrn)
    const
{
    Quadratic2 kResult;

    float fX = -rkTrn.X(), fY = -rkTrn.Y();
    kResult.m_afCoeff[0] = (*this)(fX,fY);
    kResult.m_afCoeff[1] = m_afCoeff[1] + ((float)2.0)*fX*m_afCoeff[3] +
        fY*m_afCoeff[4];
    kResult.m_afCoeff[2] = m_afCoeff[2] + ((float)2.0)*fY*m_afCoeff[5] +
        fX*m_afCoeff[4];
    kResult.m_afCoeff[3] = m_afCoeff[3];
    kResult.m_afCoeff[4] = m_afCoeff[4];
    kResult.m_afCoeff[5] = m_afCoeff[5];

    return kResult;
}
//----------------------------------------------------------------------------
inline Quadratic2 Quadratic2::Rotate (const Matrix2& rkRot) const
{
    Quadratic2 kResult;

    float fCos = rkRot[0][0], fSin = rkRot[0][1];
    float fCos2 = fCos*fCos, fSin2 = fSin*fSin, fSinCos = fSin*fCos;
    kResult.m_afCoeff[0] = m_afCoeff[0];
    kResult.m_afCoeff[1] = m_afCoeff[1]*fCos + m_afCoeff[2]*fSin;
    kResult.m_afCoeff[2] = m_afCoeff[2]*fCos - m_afCoeff[1]*fSin;
    kResult.m_afCoeff[3] = m_afCoeff[3]*fCos2 + m_afCoeff[4]*fSinCos +
        m_afCoeff[5]*fSin2;
    kResult.m_afCoeff[4] = m_afCoeff[4]*(fCos2 - fSin2) +
        ((float)2.0)*fSinCos*(m_afCoeff[5] - m_afCoeff[3]);
    kResult.m_afCoeff[5] = m_afCoeff[3]*fSin2 - m_afCoeff[4]*fSinCos +
        m_afCoeff[5]*fCos2;

    return kResult;
}
//----------------------------------------------------------------------------
inline Quadratic2 Quadratic2::Scale (const Vector2& rkScale) const
{
    Quadratic2 kResult;

    float fInvSX = ((float)1.0)/rkScale.X();
    float fInvSY = ((float)1.0)/rkScale.Y();
    kResult.m_afCoeff[0] = m_afCoeff[0];
    kResult.m_afCoeff[1] = m_afCoeff[1]*fInvSX;
    kResult.m_afCoeff[2] = m_afCoeff[2]*fInvSY;
    kResult.m_afCoeff[3] = m_afCoeff[3]*fInvSX*fInvSX;
    kResult.m_afCoeff[4] = m_afCoeff[4]*fInvSX*fInvSY;
    kResult.m_afCoeff[5] = m_afCoeff[5]*fInvSY*fInvSY;

    return kResult;
}
//----------------------------------------------------------------------------

