///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Quadratic3::Quadratic3 ()
{
    memset(m_afCoeff,0,10*sizeof(float));
}
//----------------------------------------------------------------------------
inline Quadratic3::Quadratic3 (float fA0, float fA1, float fA2, float fA3,
    float fA4, float fA5, float fA6, float fA7, float fA8, float fA9)
{
    m_afCoeff[0] = fA0;
    m_afCoeff[1] = fA1;
    m_afCoeff[2] = fA2;
    m_afCoeff[3] = fA3;
    m_afCoeff[4] = fA4;
    m_afCoeff[5] = fA5;
    m_afCoeff[6] = fA6;
    m_afCoeff[7] = fA7;
    m_afCoeff[8] = fA8;
    m_afCoeff[9] = fA9;
}
//----------------------------------------------------------------------------
inline Quadratic3::Quadratic3 (const float afA[10])
{
    size_t uiSize = 10*sizeof(float);
    System::Memcpy(m_afCoeff,afA,uiSize);
}
//----------------------------------------------------------------------------
inline Quadratic3::operator const float* () const
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline Quadratic3::operator float* ()
{
    return m_afCoeff;
}
//----------------------------------------------------------------------------
inline float Quadratic3::operator[] (int i) const
{
    assert(0 <= i && i < 10);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::operator[] (int i)
{
    assert(0 <= i && i < 10);
    return m_afCoeff[i];
}
//----------------------------------------------------------------------------
inline float Quadratic3::Constant() const
{
    return m_afCoeff[0];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::Constant()
{
    return m_afCoeff[0];
}
//----------------------------------------------------------------------------
inline float Quadratic3::X() const
{
    return m_afCoeff[1];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::X()
{
    return m_afCoeff[1];
}
//----------------------------------------------------------------------------
inline float Quadratic3::Y() const
{
    return m_afCoeff[2];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::Y()
{
    return m_afCoeff[2];
}
//----------------------------------------------------------------------------
inline float Quadratic3::Z() const
{
    return m_afCoeff[3];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::Z()
{
    return m_afCoeff[3];
}
//----------------------------------------------------------------------------
inline float Quadratic3::XX() const
{
    return m_afCoeff[4];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::XX()
{
    return m_afCoeff[4];
}
//----------------------------------------------------------------------------
inline float Quadratic3::XY() const
{
    return m_afCoeff[5];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::XY()
{
    return m_afCoeff[5];
}
//----------------------------------------------------------------------------
inline float Quadratic3::XZ() const
{
    return m_afCoeff[6];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::XZ()
{
    return m_afCoeff[6];
}
//----------------------------------------------------------------------------
inline float Quadratic3::YY() const
{
    return m_afCoeff[7];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::YY()
{
    return m_afCoeff[7];
}
//----------------------------------------------------------------------------
inline float Quadratic3::YZ() const
{
    return m_afCoeff[8];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::YZ()
{
    return m_afCoeff[8];
}
//----------------------------------------------------------------------------
inline float Quadratic3::ZZ() const
{
    return m_afCoeff[9];
}
//----------------------------------------------------------------------------
inline float& Quadratic3::ZZ()
{
    return m_afCoeff[9];
}
//----------------------------------------------------------------------------
inline void Quadratic3::Set (int iXOrder, int iYOrder, int iZOrder,
    float fCoeff)
{
    if (iXOrder >= 0 && iYOrder >= 0 && iZOrder >= 0)
    {
        int iSumYZ = iYOrder + iZOrder;
        int iSumXYZ = iXOrder + iSumYZ;
        if (iSumXYZ <= 3)
        {
            int i = iSumYZ*(1+4*iXOrder+3*iSumYZ)/2+iXOrder*iXOrder+iZOrder;
            assert(0 <= i && i < 10);
            m_afCoeff[i] = fCoeff;
        }
    }
}
//----------------------------------------------------------------------------
inline float Quadratic3::Get (int iXOrder, int iYOrder, int iZOrder) const
{
    if (iXOrder >= 0 && iYOrder >= 0 && iZOrder >= 0)
    {
        int iSumYZ = iYOrder + iZOrder;
        int iSumXYZ = iXOrder + iSumYZ;
        if (iSumXYZ <= 3)
        {
            int i = iSumYZ*(1+4*iXOrder+3*iSumYZ)/2+iXOrder*iXOrder+iZOrder;
            assert(0 <= i && i < 10);
            return m_afCoeff[i];
        }
    }

    return (float)0.0;
}
//----------------------------------------------------------------------------
inline float Quadratic3::operator() (float fX, float fY, float fZ) const
{
    float fResult = m_afCoeff[0] + fX*(m_afCoeff[1] + fX*m_afCoeff[4]) +
        fY*(m_afCoeff[2] + fX*m_afCoeff[5] + fY*m_afCoeff[7]) + fZ *
        (m_afCoeff[3] + fX*m_afCoeff[6] + fY*m_afCoeff[8] + fZ*m_afCoeff[9]);
    return fResult;
}
//----------------------------------------------------------------------------
inline float Quadratic3::operator() (const Vector3& rkP) const
{
    return (*this)(rkP.X(),rkP.Y(),rkP.Z());
}
//----------------------------------------------------------------------------
inline Quadratic3 Quadratic3::Translate (const Vector3& rkTrn)
    const
{
    Quadratic3 kResult;

    float fX = -rkTrn.X(), fY = -rkTrn.Y(), fZ = -rkTrn.Z();
    kResult.m_afCoeff[0] = (*this)(fX,fY,fZ);
    kResult.m_afCoeff[1] = m_afCoeff[1] + ((float)2.0)*fX*m_afCoeff[4] +
        fY*m_afCoeff[5] + fZ*m_afCoeff[6];
    kResult.m_afCoeff[2] = m_afCoeff[2] + ((float)2.0)*fY*m_afCoeff[7] +
        fX*m_afCoeff[5] + fZ*m_afCoeff[8];
    kResult.m_afCoeff[3] = m_afCoeff[3] + ((float)2.0)*fZ*m_afCoeff[9] +
        fX*m_afCoeff[6] + fY*m_afCoeff[8];
    kResult.m_afCoeff[4] = m_afCoeff[4];
    kResult.m_afCoeff[5] = m_afCoeff[5];
    kResult.m_afCoeff[6] = m_afCoeff[6];
    kResult.m_afCoeff[7] = m_afCoeff[7];
    kResult.m_afCoeff[8] = m_afCoeff[8];
    kResult.m_afCoeff[9] = m_afCoeff[9];

    return kResult;
}
//----------------------------------------------------------------------------
inline Quadratic3 Quadratic3::Rotate (const Matrix3& rkRot) const
{
    Quadratic3 kResult;

    // The function in matrix-vector form is
    //   Q(X) = Transpose(X)*A*X + Transpose(B)*X + C
    // The transformed function with X = Tranpose(R)*Y is
    //   P(Y) = Y*R*A*Transpose(R)*Y + Transpose(R*B)*Y + C

    Matrix3 kA;
    kA[0][0] = m_afCoeff[4];              // x*x
    kA[0][1] = ((float)0.5)*m_afCoeff[5];  // x*y/2
    kA[0][2] = ((float)0.5)*m_afCoeff[6];  // x*z/2
    kA[1][0] = kA[0][1];                  // x*y/2
    kA[1][1] = m_afCoeff[7];              // y*y
    kA[1][2] = ((float)0.5)*m_afCoeff[8];  // y*z/2
    kA[2][0] = kA[0][2];                  // x*z/2
    kA[2][1] = kA[1][2];                  // y*z/2
    kA[2][2] = m_afCoeff[9];              // z*z

    Vector3 kB;
    kB[0] = m_afCoeff[1];                 // x
    kB[1] = m_afCoeff[2];                 // y
    kB[2] = m_afCoeff[3];                 // z

    Matrix3 kNewA = rkRot*kA.TimesTranspose(rkRot);
    Vector3 kNewB = rkRot*kB;

    kResult.m_afCoeff[0] = m_afCoeff[0];
    kResult.m_afCoeff[1] = kNewB[0];
    kResult.m_afCoeff[2] = kNewB[1];
    kResult.m_afCoeff[3] = kNewB[2];
    kResult.m_afCoeff[4] = kNewA[0][0];
    kResult.m_afCoeff[5] = ((float)2.0)*kNewA[0][1];
    kResult.m_afCoeff[6] = ((float)2.0)*kNewA[0][2];
    kResult.m_afCoeff[7] = kNewA[1][1];
    kResult.m_afCoeff[8] = ((float)2.0)*kNewA[1][2];
    kResult.m_afCoeff[9] = kNewA[2][2];

    return kResult;
}
//----------------------------------------------------------------------------
inline Quadratic3 Quadratic3::Scale (const Vector3& rkScale) const
{
    Quadratic3 kResult;

    float fInvSX = ((float)1.0)/rkScale.X();
    float fInvSY = ((float)1.0)/rkScale.Y();
    float fInvSZ = ((float)1.0)/rkScale.Z();
    kResult.m_afCoeff[0] = m_afCoeff[0];
    kResult.m_afCoeff[1] = m_afCoeff[1]*fInvSX;
    kResult.m_afCoeff[2] = m_afCoeff[2]*fInvSY;
    kResult.m_afCoeff[3] = m_afCoeff[3]*fInvSZ;
    kResult.m_afCoeff[4] = m_afCoeff[4]*fInvSX*fInvSX;
    kResult.m_afCoeff[5] = m_afCoeff[5]*fInvSX*fInvSY;
    kResult.m_afCoeff[6] = m_afCoeff[6]*fInvSX*fInvSZ;
    kResult.m_afCoeff[7] = m_afCoeff[7]*fInvSY*fInvSY;
    kResult.m_afCoeff[8] = m_afCoeff[8]*fInvSY*fInvSZ;
    kResult.m_afCoeff[9] = m_afCoeff[9]*fInvSZ*fInvSZ;

    return kResult;
}
//----------------------------------------------------------------------------

