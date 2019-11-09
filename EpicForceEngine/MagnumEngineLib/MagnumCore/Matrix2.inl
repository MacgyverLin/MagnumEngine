///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (bool bZero)
{
    if (bZero)
    {
        MakeZero();
    }
    else
    {
        MakeIdentity();
    }
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (const Matrix2& rkM)
{
    size_t uiSize = 4*sizeof(float);
    System::memcpy(m_afEntry, rkM.m_afEntry,uiSize);
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (float fM00, float fM01, float fM10, float fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM10;
    m_afEntry[3] = fM11;
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (const float afEntry[4], bool bRowMajor)
{
    if (bRowMajor)
    {
        size_t uiSize = 4*sizeof(float);
        memcpy(m_afEntry,afEntry,uiSize);
    }
    else
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[2];
        m_afEntry[2] = afEntry[1];
        m_afEntry[3] = afEntry[3];
    }
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (const Vector2& rkU, const Vector2& rkV, bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkV[0];
        m_afEntry[2] = rkU[1];
        m_afEntry[3] = rkV[1];
    }
    else
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkU[1];
        m_afEntry[2] = rkV[0];
        m_afEntry[3] = rkV[1];
    }
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (const Vector2* akV, bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[1][0];
        m_afEntry[2] = akV[0][1];
        m_afEntry[3] = akV[1][1];
    }
    else
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[0][1];
        m_afEntry[2] = akV[1][0];
        m_afEntry[3] = akV[1][1];
    }
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (float fM00, float fM11)
{
    MakeDiagonal(fM00,fM11);
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (float fAngle)
{
    FromAngle(fAngle);
}
//----------------------------------------------------------------------------

inline Matrix2::Matrix2 (const Vector2& rkU, const Vector2& rkV)
{
    MakeTensorProduct(rkU,rkV);
}
//----------------------------------------------------------------------------

inline void Matrix2::Set (float fM00, float fM01, float fM10, float fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM10;
    m_afEntry[3] = fM11;
}
//----------------------------------------------------------------------------

inline Matrix2::operator const float* () const
{
    return m_afEntry;
}
//----------------------------------------------------------------------------

inline Matrix2::operator float* ()
{
    return m_afEntry;
}
//----------------------------------------------------------------------------

inline const float* Matrix2::operator[] (int iRow) const
{
    return &m_afEntry[2*iRow];
}
//----------------------------------------------------------------------------

inline float* Matrix2::operator[] (int iRow)
{
    return &m_afEntry[2*iRow];
}
//----------------------------------------------------------------------------

inline float Matrix2::operator() (int iRow, int iCol) const
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------

inline float& Matrix2::operator() (int iRow, int iCol)
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------

inline int Matrix2::I (int iRow, int iCol)
{
    assert(0 <= iRow && iRow < 2 && 0 <= iCol && iCol < 2);
    return iCol + 2*iRow;
}
//----------------------------------------------------------------------------

inline void Matrix2::MakeZero ()
{
    memset(m_afEntry,0,4*sizeof(float));
}
//----------------------------------------------------------------------------

inline void Matrix2::MakeIdentity ()
{
    m_afEntry[0] = (float)1.0;
    m_afEntry[1] = (float)0.0;
    m_afEntry[2] = (float)0.0;
    m_afEntry[3] = (float)1.0;
}
//----------------------------------------------------------------------------

inline void Matrix2::MakeDiagonal (float fM00, float fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = (float)0.0;
    m_afEntry[2] = (float)0.0;
    m_afEntry[3] = fM11;
}
//----------------------------------------------------------------------------

inline void Matrix2::FromAngle (float fAngle)
{
    m_afEntry[0] = Math::Cos(fAngle);
    m_afEntry[2] = Math::Sin(fAngle);
    m_afEntry[1] = -m_afEntry[2];
    m_afEntry[3] =  m_afEntry[0];
}
//----------------------------------------------------------------------------

inline void Matrix2::MakeTensorProduct (const Vector2& rkU, const Vector2& rkV)
{
    m_afEntry[0] = rkU[0]*rkV[0];
    m_afEntry[1] = rkU[0]*rkV[1];
    m_afEntry[2] = rkU[1]*rkV[0];
    m_afEntry[3] = rkU[1]*rkV[1];
}
//----------------------------------------------------------------------------

inline void Matrix2::SetRow (int iRow, const Vector2& rkV)
{
    assert(0 <= iRow && iRow < 2);
    for (int iCol = 0, i = 2*iRow; iCol < 2; iCol++, i++)
    {
        m_afEntry[i] = rkV[iCol];
    }
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2::GetRow (int iRow) const
{
    assert(0 <= iRow && iRow < 2);
    Vector2 kV;
    for (int iCol = 0, i = 2*iRow; iCol < 2; iCol++, i++)
    {
        kV[iCol] = m_afEntry[i];
    }
    return kV;
}
//----------------------------------------------------------------------------

inline void Matrix2::SetColumn (int iCol, const Vector2& rkV)
{
    assert(0 <= iCol && iCol < 2);
    for (int iRow = 0, i = iCol; iRow < 2; iRow++, i += 2)
    {
        m_afEntry[i] = rkV[iRow];
    }
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2::GetColumn (int iCol) const
{
    assert(0 <= iCol && iCol < 2);
    Vector2 kV;
    for (int iRow = 0, i = iCol; iRow < 2; iRow++, i += 2)
    {
        kV[iRow] = m_afEntry[i];
    }
    return kV;
}
//----------------------------------------------------------------------------

inline void Matrix2::GetColumnMajor (float* afCMajor) const
{
    for (int iRow = 0, i = 0; iRow < 2; iRow++)
    {
        for (int iCol = 0; iCol < 2; iCol++)
        {
            afCMajor[i++] = m_afEntry[I(iCol,iRow)];
        }
    }
}
//----------------------------------------------------------------------------

inline Matrix2& Matrix2::operator= (const Matrix2& rkM)
{
    size_t uiSize = 4*sizeof(float);
    memcpy(m_afEntry,rkM.m_afEntry,uiSize);
    return *this;
}
//----------------------------------------------------------------------------

inline int Matrix2::CompareArrays (const Matrix2& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,4*sizeof(float));
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator== (const Matrix2& rkM) const
{
    return CompareArrays(rkM) == 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator!= (const Matrix2& rkM) const
{
    return CompareArrays(rkM) != 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator<  (const Matrix2& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator<= (const Matrix2& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator>  (const Matrix2& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2::operator>= (const Matrix2& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator+ (const Matrix2& rkM) const
{
    Matrix2 kSum;
    for (int i = 0; i < 4; i++)
    {
        kSum.m_afEntry[i] = m_afEntry[i] + rkM.m_afEntry[i];
    }
    return kSum;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator- (const Matrix2& rkM) const
{
    Matrix2 kDiff;
    for (int i = 0; i < 4; i++)
    {
        kDiff.m_afEntry[i] = m_afEntry[i] - rkM.m_afEntry[i];
    }
    return kDiff;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator* (const Matrix2& rkM) const
{
    Matrix2 kProd;
    for (int iRow = 0; iRow < 2; iRow++)
    {
        for (int iCol = 0; iCol < 2; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 2; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator* (float fScalar) const
{
    Matrix2 kProd;
    for (int i = 0; i < 4; i++)
    {
        kProd.m_afEntry[i] = fScalar*m_afEntry[i];
    }
    return kProd;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator/ (float fScalar) const
{
    Matrix2 kQuot;
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afEntry[i] = fInvScalar*m_afEntry[i];
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afEntry[i] = Math::MAX_REAL;
        }
    }

    return kQuot;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::operator- () const
{
    Matrix2 kNeg;
    for (int i = 0; i < 4; i++)
    {
        kNeg.m_afEntry[i] = -m_afEntry[i];
    }
    return kNeg;
}
//----------------------------------------------------------------------------

inline Matrix2& Matrix2::operator+= (const Matrix2& rkM)
{
    for (int i = 0; i < 4; i++)
    {
        m_afEntry[i] += rkM.m_afEntry[i];
    }
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2& Matrix2::operator-= (const Matrix2& rkM)
{
    for (int i = 0; i < 4; i++)
    {
        m_afEntry[i] -= rkM.m_afEntry[i];
    }
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2& Matrix2::operator*= (float fScalar)
{
    for (int i = 0; i < 4; i++)
    {
        m_afEntry[i] *= fScalar;
    }
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2& Matrix2::operator/= (float fScalar)
{
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
        {
            m_afEntry[i] *= fInvScalar;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            m_afEntry[i] = Math::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2::operator* (const Vector2& rkV) const
{
    Vector2 kProd;
    for (int iRow = 0; iRow < 2; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 2; iCol++)
        {
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::Transpose () const
{
    Matrix2 kTranspose;
    for (int iRow = 0; iRow < 2; iRow++)
    {
        for (int iCol = 0; iCol < 2; iCol++)
        {
            kTranspose.m_afEntry[I(iRow,iCol)] = m_afEntry[I(iCol,iRow)];
        }
    }
    return kTranspose;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::TransposeTimes (const Matrix2& rkM) const
{
    // P = A^T*B, P[r][c] = sum_m A[m][r]*B[m][c]
    Matrix2 kProd;
    for (int iRow = 0; iRow < 2; iRow++)
    {
        for (int iCol = 0; iCol < 2; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 2; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iMid,iRow)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::TimesTranspose (const Matrix2& rkM) const
{
    // P = A*B^T, P[r][c] = sum_m A[r][m]*B[c][m]
    Matrix2 kProd;
    for (int iRow = 0; iRow < 2; iRow++)
    {
        for (int iCol = 0; iCol < 2; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 2; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iCol,iMid)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::Inverse () const
{
    Matrix2 kInverse;

    float fDet = m_afEntry[0]*m_afEntry[3] - m_afEntry[1]*m_afEntry[2];
    if (Math::FAbs(fDet) > Math::ZERO_TOLERANCE)
    {
        float fInvDet = ((float)1.0)/fDet;
        kInverse[0][0] =  m_afEntry[3]*fInvDet;
        kInverse[0][1] = -m_afEntry[1]*fInvDet;
        kInverse[1][0] = -m_afEntry[2]*fInvDet;
        kInverse[1][1] =  m_afEntry[0]*fInvDet;
    }
    else
    {
        kInverse.MakeZero();
    }

    return kInverse;
}
//----------------------------------------------------------------------------

inline Matrix2 Matrix2::Adjoint () const
{
    return Matrix2(
         m_afEntry[3],-m_afEntry[1],
        -m_afEntry[2], m_afEntry[0]);
}
//----------------------------------------------------------------------------

inline float Matrix2::Determinant () const
{
    return m_afEntry[0]*m_afEntry[3] - m_afEntry[1]*m_afEntry[2];
}
//----------------------------------------------------------------------------

inline float Matrix2::QForm (const Vector2& rkU,
    const Vector2& rkV) const
{
    return rkU.Dot((*this)*rkV);
}
//----------------------------------------------------------------------------

inline void Matrix2::ToAngle (float& rfAngle) const
{
    // assert:  matrix is a rotation
    rfAngle = Math::ATan2(m_afEntry[2],m_afEntry[0]);
}
//----------------------------------------------------------------------------

inline void Matrix2::Orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1], then orthonormal output matrix is Q = [q0|q1],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    float fInvLength = Math::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[2]*m_afEntry[2]);

    m_afEntry[0] *= fInvLength;
    m_afEntry[2] *= fInvLength;

    // compute q1
    float fDot0 = m_afEntry[0]*m_afEntry[1] + m_afEntry[2]*m_afEntry[3];
    m_afEntry[1] -= fDot0*m_afEntry[0];
    m_afEntry[3] -= fDot0*m_afEntry[2];

    fInvLength = Math::InvSqrt(m_afEntry[1]*m_afEntry[1] +
        m_afEntry[3]*m_afEntry[3]);

    m_afEntry[1] *= fInvLength;
    m_afEntry[3] *= fInvLength;
}
//----------------------------------------------------------------------------

inline void Matrix2::EigenDecomposition (Matrix2& rkRot, Matrix2& rkDiag) const
{
    float fTrace = m_afEntry[0] + m_afEntry[3];
    float fDiff = m_afEntry[0] - m_afEntry[3];
    float fDiscr = Math::Sqrt(fDiff*fDiff +
        ((float)4.0)*m_afEntry[1]*m_afEntry[1]);
    float fEVal0 = ((float)0.5)*(fTrace-fDiscr);
    float fEVal1 = ((float)0.5)*(fTrace+fDiscr);
    rkDiag.MakeDiagonal(fEVal0,fEVal1);

    float fCos, fSin;
    if (fDiff >= (float)0.0)
    {
        fCos = m_afEntry[1];
        fSin = fEVal0 - m_afEntry[0];
    }
    else
    {
        fCos = fEVal0 - m_afEntry[3];
        fSin = m_afEntry[1];
    }
    float fTmp = Math::InvSqrt(fCos*fCos + fSin*fSin);
    fCos *= fTmp;
    fSin *= fTmp;

    rkRot.m_afEntry[0] = fCos;
    rkRot.m_afEntry[1] = -fSin;
    rkRot.m_afEntry[2] = fSin;
    rkRot.m_afEntry[3] = fCos;
}
//----------------------------------------------------------------------------

inline Matrix2 operator* (float fScalar, const Matrix2& rkM)
{
    return rkM*fScalar;
}
//----------------------------------------------------------------------------

inline Vector2 operator* (const Vector2& rkV, const Matrix2& rkM)
{
    return Vector2(
        rkV[0]*rkM[0][0] + rkV[1]*rkM[1][0],
        rkV[0]*rkM[0][1] + rkV[1]*rkM[1][1]);
}
//----------------------------------------------------------------------------

inline void Matrix2::read(InputStream &is)
{
	for(int i=0; i<4; i++)
		is >> m_afEntry[i];
}

//----------------------------------------------------------------------------
inline void Matrix2::write(OutputStream &os) const
{
	for(int i=0; i<4; i++)
		os << m_afEntry[i];
}
