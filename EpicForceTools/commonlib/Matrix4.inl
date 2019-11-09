///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Matrix4::Matrix4 (bool bZero)
{
    if (bZero)
    {
        initZero();
    }
    else
    {
        initIdentity();
    }
}
//----------------------------------------------------------------------------
inline Matrix4::Matrix4 (const Matrix4& rkM)
{
    size_t uiSize = 16*sizeof(float);
    memcpy(m_afEntry,rkM.m_afEntry,uiSize);
}
//----------------------------------------------------------------------------
inline Matrix4::Matrix4 (float fM00, float fM01, float fM02, float fM03,
						 float fM10, float fM11, float fM12, float fM13, 
						 float fM20, float fM21, float fM22, float fM23, 
						 float fM30, float fM31, float fM32, float fM33)
{
    m_afEntry[ 0] = fM00;
    m_afEntry[ 1] = fM01;
    m_afEntry[ 2] = fM02;
    m_afEntry[ 3] = fM03;
    m_afEntry[ 4] = fM10;
    m_afEntry[ 5] = fM11;
    m_afEntry[ 6] = fM12;
    m_afEntry[ 7] = fM13;
    m_afEntry[ 8] = fM20;
    m_afEntry[ 9] = fM21;
    m_afEntry[10] = fM22;
    m_afEntry[11] = fM23;
    m_afEntry[12] = fM30;
    m_afEntry[13] = fM31;
    m_afEntry[14] = fM32;
    m_afEntry[15] = fM33;
}
//----------------------------------------------------------------------------
inline Matrix4::Matrix4 (const float afEntry[16], bool bRowMajor)
{
    if (bRowMajor)
    {
        size_t uiSize = 16*sizeof(float);
        memcpy(m_afEntry,afEntry,uiSize);
    }
    else
    {
        m_afEntry[ 0] = afEntry[ 0];
        m_afEntry[ 1] = afEntry[ 4];
        m_afEntry[ 2] = afEntry[ 8];
        m_afEntry[ 3] = afEntry[12];
        m_afEntry[ 4] = afEntry[ 1];
        m_afEntry[ 5] = afEntry[ 5];
        m_afEntry[ 6] = afEntry[ 9];
        m_afEntry[ 7] = afEntry[13];
        m_afEntry[ 8] = afEntry[ 2];
        m_afEntry[ 9] = afEntry[ 6];
        m_afEntry[10] = afEntry[10];
        m_afEntry[11] = afEntry[14];
        m_afEntry[12] = afEntry[ 3];
        m_afEntry[13] = afEntry[ 7];
        m_afEntry[14] = afEntry[11];
        m_afEntry[15] = afEntry[15];
    }
}

//----------------------------------------------------------------------------
inline void Matrix4::Set (float fM00, float fM01, float fM02, float fM03,
						  float fM10, float fM11, float fM12, float fM13, 
						  float fM20, float fM21, float fM22, float fM23, 
						  float fM30, float fM31, float fM32, float fM33)
{
    m_afEntry[ 0] = fM00;
    m_afEntry[ 1] = fM01;
    m_afEntry[ 2] = fM02;
    m_afEntry[ 3] = fM03;
    m_afEntry[ 4] = fM10;
    m_afEntry[ 5] = fM11;
    m_afEntry[ 6] = fM12;
    m_afEntry[ 7] = fM13;
    m_afEntry[ 8] = fM20;
    m_afEntry[ 9] = fM21;
    m_afEntry[10] = fM22;
    m_afEntry[11] = fM23;
    m_afEntry[12] = fM30;
    m_afEntry[13] = fM31;
    m_afEntry[14] = fM32;
    m_afEntry[15] = fM33;
}

//----------------------------------------------------------------------------
inline Matrix4::operator const float* () const
{
    return m_afEntry;
}
//----------------------------------------------------------------------------
inline Matrix4::operator float* ()
{
    return m_afEntry;
}
//----------------------------------------------------------------------------
inline const float* Matrix4::operator[] (int iRow) const
{
    return &m_afEntry[RowStartIdxs[iRow]];
}
//----------------------------------------------------------------------------
inline float* Matrix4::operator[] (int iRow)
{
    return &m_afEntry[RowStartIdxs[iRow]];
}
//----------------------------------------------------------------------------
inline float Matrix4::operator() (int iRow, int iCol) const
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------
inline float& Matrix4::operator() (int iRow, int iCol)
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------
inline int Matrix4::I (int iRow, int iCol)
{
    assert(0 <= iRow && iRow < 4 && 0 <= iCol && iCol < 4);
	
    // return iCol + 4*iRow;
	return iCol + RowStartIdxs[iRow];
}
//----------------------------------------------------------------------------
inline void Matrix4::SetRow (int iRow, const Vector4& rkV)
{
    assert(0 <= iRow && iRow < 4);
    for (int iCol = 0, i = RowStartIdxs[iRow]; iCol < 4; iCol++, i++)
    {
        m_afEntry[i] = rkV[iCol];
    }
}
//----------------------------------------------------------------------------
inline Vector4 Matrix4::GetRow (int iRow) const
{
    assert(0 <= iRow && iRow < 4);
    Vector4 kV;
    for (int iCol = 0, i = RowStartIdxs[iRow]; iCol < 4; iCol++, i++)
    {
        kV[iCol] = m_afEntry[i];
    }
    return kV;
}
//----------------------------------------------------------------------------
inline void Matrix4::SetColumn (int iCol, const Vector4& rkV)
{
    assert(0 <= iCol && iCol < 4);
    for (int iRow = 0, i = iCol; iRow < 4; iRow++, i += 4)
    {
        m_afEntry[i] = rkV[iRow];
    }
}
//----------------------------------------------------------------------------
inline Vector4 Matrix4::GetColumn (int iCol) const
{
    assert(0 <= iCol && iCol < 4);
    Vector4 kV;
    for (int iRow = 0, i = iCol; iRow < 4; iRow++, i += 4)
    {
        kV[iRow] = m_afEntry[i];
    }
    return kV;
}
//----------------------------------------------------------------------------
inline void Matrix4::GetColumnMajor (float* afCMajor) const
{
    for (int iRow = 0, i = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            afCMajor[i++] = m_afEntry[I(iCol,iRow)];
        }
    }
}
//----------------------------------------------------------------------------
inline Matrix4& Matrix4::operator= (const Matrix4& rkM)
{
    size_t uiSize = 16*sizeof(float);
    memcpy(m_afEntry,rkM.m_afEntry,uiSize);
    return *this;
}
//----------------------------------------------------------------------------
inline int Matrix4::CompareArrays (const Matrix4& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,16*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator== (const Matrix4& rkM) const
{
    return CompareArrays(rkM) == 0;
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator!= (const Matrix4& rkM) const
{
    return CompareArrays(rkM) != 0;
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator<  (const Matrix4& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator<= (const Matrix4& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator>  (const Matrix4& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------
inline bool Matrix4::operator>= (const Matrix4& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator+ (const Matrix4& rkM) const
{
    Matrix4 kSum;
    for (int i = 0; i < 16; i++)
    {
        kSum.m_afEntry[i] = m_afEntry[i] + rkM.m_afEntry[i];
    }
    return kSum;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator- (const Matrix4& rkM) const
{
    Matrix4 kDiff;
    for (int i = 0; i < 16; i++)
    {
        kDiff.m_afEntry[i] = m_afEntry[i] - rkM.m_afEntry[i];
    }
    return kDiff;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator* (const Matrix4& rkM) const
{
    Matrix4 kProd;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 4; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator* (float fScalar) const
{
    Matrix4 kProd;
    for (int i = 0; i < 16; i++)
    {
        kProd.m_afEntry[i] = fScalar*m_afEntry[i];
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator/ (float fScalar) const
{
    Matrix4 kQuot;
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 16; i++)
        {
            kQuot.m_afEntry[i] = fInvScalar*m_afEntry[i];
        }
    }
    else
    {
        for (i = 0; i < 16; i++)
        {
            kQuot.m_afEntry[i] = Math::MAX_REAL;
        }
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::operator- () const
{
    Matrix4 kNeg;
    for (int i = 0; i < 16; i++)
    {
        kNeg.m_afEntry[i] = -m_afEntry[i];
    }
    return kNeg;
}
//----------------------------------------------------------------------------
inline Matrix4& Matrix4::operator+= (const Matrix4& rkM)
{
    for (int i = 0; i < 16; i++)
    {
        m_afEntry[i] += rkM.m_afEntry[i];
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Matrix4& Matrix4::operator-= (const Matrix4& rkM)
{
    for (int i = 0; i < 16; i++)
    {
        m_afEntry[i] -= rkM.m_afEntry[i];
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Matrix4& Matrix4::operator*= (float fScalar)
{
    for (int i = 0; i < 16; i++)
    {
        m_afEntry[i] *= fScalar;
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Matrix4& Matrix4::operator/= (float fScalar)
{
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 16; i++)
        {
            m_afEntry[i] *= fInvScalar;
        }
    }
    else
    {
        for (i = 0; i < 16; i++)
        {
            m_afEntry[i] = Math::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
inline Vector4 Matrix4::operator* (const Vector4& rkV) const
{
    Vector4 kProd;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 4; iCol++)
        {
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
        }
            
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Vector3 Matrix4::operator* (const Vector3& rkV) const
{
    Vector3 kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 3; iCol++)
        {
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
        }
		kProd[iRow] += m_afEntry[I(iRow, 3)];
    }
    return kProd;
}
//----------------------------------------------------------------------------
/*
inline Vector4 Matrix4::TimesPositionVector(const Vector4& rkV) const
{
	return *this * rkV;
}
*/
//----------------------------------------------------------------------------
inline Vector3 Matrix4::TimesPositionVector(const Vector3& rkV) const
{
	return *this * rkV;
}
/*
//----------------------------------------------------------------------------
inline Vector4 Matrix4::TimesDirectionVector(const Vector4& rkV) const
{
    Vector3 kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 3; iCol++)
        {
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
        }
    }
    return kProd;
}
*/
//----------------------------------------------------------------------------
inline Vector3 Matrix4::TimesDirectionVector(const Vector3& rkV) const
{
    Vector3 kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 3; iCol++)
        {
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
        }
    }
    return kProd;
}

//----------------------------------------------------------------------------
inline Matrix4 Matrix4::Transpose () const
{
    Matrix4 kTranspose;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            kTranspose.m_afEntry[I(iRow,iCol)] = m_afEntry[I(iCol,iRow)];
        }
    }
    return kTranspose;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::TransposeTimes (const Matrix4& rkM) const
{
    // P = A^T*B, P[r][c] = sum_m A[m][r]*B[m][c]
    Matrix4 kProd;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 4; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iMid,iRow)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::TimesTranspose (const Matrix4& rkM) const
{
    // P = A*B^T, P[r][c] = sum_m A[r][m]*B[c][m]
    Matrix4 kProd;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 4; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iCol,iMid)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::Inverse () const
{
    float fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    float fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    float fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    float fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    float fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    float fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    float fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    float fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    float fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    float fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    float fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    float fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];

    float fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    if (Math::FAbs(fDet) <= Math::ZERO_TOLERANCE)
    {
        return Matrix4::ZERO;
    }

    Matrix4 kInv;
    kInv[0][0] = + m_afEntry[ 5]*fB5 - m_afEntry[ 6]*fB4 + m_afEntry[ 7]*fB3;
    kInv[1][0] = - m_afEntry[ 4]*fB5 + m_afEntry[ 6]*fB2 - m_afEntry[ 7]*fB1;
    kInv[2][0] = + m_afEntry[ 4]*fB4 - m_afEntry[ 5]*fB2 + m_afEntry[ 7]*fB0;
    kInv[3][0] = - m_afEntry[ 4]*fB3 + m_afEntry[ 5]*fB1 - m_afEntry[ 6]*fB0;
    kInv[0][1] = - m_afEntry[ 1]*fB5 + m_afEntry[ 2]*fB4 - m_afEntry[ 3]*fB3;
    kInv[1][1] = + m_afEntry[ 0]*fB5 - m_afEntry[ 2]*fB2 + m_afEntry[ 3]*fB1;
    kInv[2][1] = - m_afEntry[ 0]*fB4 + m_afEntry[ 1]*fB2 - m_afEntry[ 3]*fB0;
    kInv[3][1] = + m_afEntry[ 0]*fB3 - m_afEntry[ 1]*fB1 + m_afEntry[ 2]*fB0;
    kInv[0][2] = + m_afEntry[13]*fA5 - m_afEntry[14]*fA4 + m_afEntry[15]*fA3;
    kInv[1][2] = - m_afEntry[12]*fA5 + m_afEntry[14]*fA2 - m_afEntry[15]*fA1;
    kInv[2][2] = + m_afEntry[12]*fA4 - m_afEntry[13]*fA2 + m_afEntry[15]*fA0;
    kInv[3][2] = - m_afEntry[12]*fA3 + m_afEntry[13]*fA1 - m_afEntry[14]*fA0;
    kInv[0][3] = - m_afEntry[ 9]*fA5 + m_afEntry[10]*fA4 - m_afEntry[11]*fA3;
    kInv[1][3] = + m_afEntry[ 8]*fA5 - m_afEntry[10]*fA2 + m_afEntry[11]*fA1;
    kInv[2][3] = - m_afEntry[ 8]*fA4 + m_afEntry[ 9]*fA2 - m_afEntry[11]*fA0;
    kInv[3][3] = + m_afEntry[ 8]*fA3 - m_afEntry[ 9]*fA1 + m_afEntry[10]*fA0;

    float fInvDet = ((float)1.0)/fDet;
    for (int iRow = 0; iRow < 4; iRow++)
    {
        for (int iCol = 0; iCol < 4; iCol++)
        {
            kInv[iRow][iCol] *= fInvDet;
        }
    }

    return kInv;
}
//----------------------------------------------------------------------------
inline Matrix4 Matrix4::Adjoint () const
{
    float fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    float fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    float fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    float fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    float fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    float fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    float fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    float fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    float fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    float fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    float fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    float fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];

    Matrix4 kAdj;
    kAdj[0][0] = + m_afEntry[ 5]*fB5 - m_afEntry[ 6]*fB4 + m_afEntry[ 7]*fB3;
    kAdj[1][0] = - m_afEntry[ 4]*fB5 + m_afEntry[ 6]*fB2 - m_afEntry[ 7]*fB1;
    kAdj[2][0] = + m_afEntry[ 4]*fB4 - m_afEntry[ 5]*fB2 + m_afEntry[ 7]*fB0;
    kAdj[3][0] = - m_afEntry[ 4]*fB3 + m_afEntry[ 5]*fB1 - m_afEntry[ 6]*fB0;
    kAdj[0][1] = - m_afEntry[ 1]*fB5 + m_afEntry[ 2]*fB4 - m_afEntry[ 3]*fB3;
    kAdj[1][1] = + m_afEntry[ 0]*fB5 - m_afEntry[ 2]*fB2 + m_afEntry[ 3]*fB1;
    kAdj[2][1] = - m_afEntry[ 0]*fB4 + m_afEntry[ 1]*fB2 - m_afEntry[ 3]*fB0;
    kAdj[3][1] = + m_afEntry[ 0]*fB3 - m_afEntry[ 1]*fB1 + m_afEntry[ 2]*fB0;
    kAdj[0][2] = + m_afEntry[13]*fA5 - m_afEntry[14]*fA4 + m_afEntry[15]*fA3;
    kAdj[1][2] = - m_afEntry[12]*fA5 + m_afEntry[14]*fA2 - m_afEntry[15]*fA1;
    kAdj[2][2] = + m_afEntry[12]*fA4 - m_afEntry[13]*fA2 + m_afEntry[15]*fA0;
    kAdj[3][2] = - m_afEntry[12]*fA3 + m_afEntry[13]*fA1 - m_afEntry[14]*fA0;
    kAdj[0][3] = - m_afEntry[ 9]*fA5 + m_afEntry[10]*fA4 - m_afEntry[11]*fA3;
    kAdj[1][3] = + m_afEntry[ 8]*fA5 - m_afEntry[10]*fA2 + m_afEntry[11]*fA1;
    kAdj[2][3] = - m_afEntry[ 8]*fA4 + m_afEntry[ 9]*fA2 - m_afEntry[11]*fA0;
    kAdj[3][3] = + m_afEntry[ 8]*fA3 - m_afEntry[ 9]*fA1 + m_afEntry[10]*fA0;

    return kAdj;
}
//----------------------------------------------------------------------------
inline float Matrix4::Determinant () const
{
    float fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    float fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    float fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    float fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    float fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    float fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    float fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    float fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    float fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    float fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    float fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    float fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];
    float fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    return fDet;
}
//----------------------------------------------------------------------------
inline float Matrix4::QForm (const Vector4& rkU,
    const Vector4& rkV) const
{
    return rkU.Dot((*this)*rkV);
}

//----------------------------------------------------------------------------
inline void Matrix4::initZero ()
{
    memset(m_afEntry,0,16*sizeof(float));
}
//----------------------------------------------------------------------------
inline void Matrix4::initIdentity ()
{
    m_afEntry[ 0] = (float)1.0;
    m_afEntry[ 1] = (float)0.0;
    m_afEntry[ 2] = (float)0.0;
    m_afEntry[ 3] = (float)0.0;
    m_afEntry[ 4] = (float)0.0;
    m_afEntry[ 5] = (float)1.0;
    m_afEntry[ 6] = (float)0.0;
    m_afEntry[ 7] = (float)0.0;
    m_afEntry[ 8] = (float)0.0;
    m_afEntry[ 9] = (float)0.0;
    m_afEntry[10] = (float)1.0;
    m_afEntry[11] = (float)0.0;
    m_afEntry[12] = (float)0.0;
    m_afEntry[13] = (float)0.0;
    m_afEntry[14] = (float)0.0;
    m_afEntry[15] = (float)1.0;
}
//----------------------------------------------------------------------------
inline void Matrix4::initTranslate(float x, float y, float z)
{
	initIdentity ();
    m_afEntry[3]  = x;
    m_afEntry[7]  = y;
    m_afEntry[11] = z;
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateX(float radian)
{
	initIdentity ();
	float cosine = Math::Cos(radian);
	float sine   = Math::Sin(radian);

	(*this)[1][1] =  cosine;
	(*this)[2][1] =    sine;
	(*this)[1][2] =   -sine;
	(*this)[2][2] =  cosine;
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateY(float radian)
{
	initIdentity ();
	float cosine = Math::Cos(radian);
	float sine   = Math::Sin(radian);

	(*this)[0][0] =  cosine;
	(*this)[2][0] =   -sine;
	(*this)[0][2] =    sine;
	(*this)[2][2] =  cosine;
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateZ(float radian)
{
	initIdentity ();
	float cosine = Math::Cos(radian);
	float sine   = Math::Sin(radian);

	(*this)[0][0] = cosine;
	(*this)[1][0] =   sine;
	(*this)[0][1] =  -sine;
	(*this)[1][1] = cosine;
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateAxisAngle(const Vector3 &axis, float radian)
{
	this->initIdentity();

	float fCos         = Math::Cos(-radian);
    float fSin         = Math::Sin(-radian);
    float fOneMinusCos = 1.0f - fCos;
    float fX2          = axis[0]*axis[0];
    float fY2          = axis[1]*axis[1];
    float fZ2          = axis[2]*axis[2];
    float fXYM         = axis[0]*axis[1]*fOneMinusCos;
    float fXZM         = axis[0]*axis[2]*fOneMinusCos;
    float fYZM         = axis[1]*axis[2]*fOneMinusCos;
    float fXSin        = axis[0]*fSin;
    float fYSin        = axis[1]*fSin;
    float fZSin        = axis[2]*fSin;
    
    (*this)[0][0]	 = fX2*fOneMinusCos+fCos;
    (*this)[0][1]	 = fXYM+fZSin;
    (*this)[0][2]	 = fXZM-fYSin;
    
    (*this)[1][0]    = fXYM-fZSin;
	(*this)[1][1]	 = fY2*fOneMinusCos+fCos;
    (*this)[1][2]	 = fYZM+fXSin;
    
    (*this)[2][0]	 = fXZM+fYSin;
    (*this)[2][1]	 = fYZM-fXSin;
    (*this)[2][2]	 = fZ2*fOneMinusCos+fCos;
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateZXY(float rz, float rx, float ry)
{
	initTranslateRotZXYScale(0, 0, 0, rz, rx, ry, 1);
}
//----------------------------------------------------------------------------
inline void Matrix4::initRotateZYX(float rz, float ry, float rx)
{
	initTranslateRotZYXScale(0, 0, 0, rz, ry, rx, 1);
}
//----------------------------------------------------------------------------
inline void Matrix4::initScale(float scale)
{
	this->initScale(scale, scale, scale);
}
//----------------------------------------------------------------------------
inline void Matrix4::initScale(float x, float y, float z)
{
	this->initIdentity();
	(*this)[0][0] = x;
	(*this)[1][1] = y;
	(*this)[2][2] = z;
}
//----------------------------------------------------------------------------
inline void Matrix4::initTranslateRotZXYScale(float tx, float ty, float tz, float rz, float rx, float ry, float scale)
{
	Matrix4 mx, my, mz, mscale, temp1, temp2;

	mx.initRotateX(rx);
	my.initRotateY(ry);
	mz.initRotateZ(rz);
	mscale.initScale(scale);

	temp1 = mz*mx;
	temp2 = temp1*my;
	*this = temp2*mscale;

	m_afEntry[3]  = tx;
	m_afEntry[7]  = ty;
	m_afEntry[11] = tz;
}
//----------------------------------------------------------------------------
inline void Matrix4::initTranslateRotZYXScale(float tx, float ty, float tz, float rz, float ry, float rx, float scale)
{
	Matrix4 mx, my, mz, mscale, temp1, temp2;

	mx.initRotateX(rx);
	my.initRotateY(ry);
	mz.initRotateZ(rz);
	mscale.initScale(scale);

	temp1 = mz*my;
	temp2 = temp1*mx;
	*this = temp2*mscale;

	m_afEntry[3]  = tx;
	m_afEntry[7]  = ty;
	m_afEntry[11] = tz;
}

inline void Matrix4::initTranslateRotZYXScale(float tx, float ty, float tz, 
	                                          float rx, float ry, float rz, 
											  float sx, float sy, float sz)
{
	Matrix4 mx, my, mz, mscale, temp1, temp2;

	mx.initRotateX(rx);
	my.initRotateY(ry);
	mz.initRotateZ(rz);
	mscale.initScale(sx, sy, sz);

	*this = mz*my*mx*mscale;
	//*this = mz*mx*my*mscale;
	//*this = mx*my*mz*mscale;
	//*this = mx*mz*my*mscale;
	//*this = my*mx*mz*mscale;
	//*this = my*mz*mx*mscale;

	m_afEntry[3]  = tx;
	m_afEntry[7]  = ty;
	m_afEntry[11] = tz;
}

//----------------------------------------------------------------------------
inline void Matrix4::initTranslateRotAxisAngleScale(float tx, float ty, float tz, const Vector3 &axis, const float radian, float scale)
{
	initRotateAxisAngle(axis, radian);

	m_afEntry[3]  = tx;
	m_afEntry[7]  = ty;
	m_afEntry[11] = tz;
}
//----------------------------------------------------------------------------
inline void Matrix4::initTranslateScale(float tx, float ty, float tz, float scale)
{
	initScale(scale);

	m_afEntry[3]  = tx;
	m_afEntry[7]  = ty;
	m_afEntry[11] = tz;
}
//----------------------------------------------------------------------------
inline void Matrix4::initLookAt(const Vector3 &position, const Vector3 &objective, const Vector3 &up)
{
	initLookAtScale(position, objective, up, 1);
}
//----------------------------------------------------------------------------
inline void Matrix4::initLookAtScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale)
{
// Right Hand
	Vector3 zaxis = position - objective      ; zaxis.Normalize();
	Vector3 yaxis = up - zaxis * up.Dot(zaxis); yaxis.Normalize();
	Vector3 xaxis = yaxis.Cross(zaxis);

	xaxis *= scale;
	yaxis *= scale;
	zaxis *= scale;

	(*this)[0][0] = xaxis.X();
	(*this)[0][1] = yaxis.X();
	(*this)[0][2] = zaxis.X();
	(*this)[0][3] = position.X();
	(*this)[1][0] = xaxis.Y();
	(*this)[1][1] = yaxis.Y();
	(*this)[1][2] = zaxis.Y();
	(*this)[1][3] = position.Y();
	(*this)[2][0] = xaxis.Z();
	(*this)[2][1] = yaxis.Z();
	(*this)[2][2] = zaxis.Z();	
	(*this)[2][3] = position.Z();
	(*this)[3][0] = 0;
	(*this)[3][1] = 0;
	(*this)[3][2] = 0;
	(*this)[3][3] = 1;
}
//----------------------------------------------------------------------------
inline void Matrix4::initStandOn(const Vector3 &position, const Vector3 &objective, const Vector3 &up)
{
	initStandOnScale(position, objective, up, 1);
}
//----------------------------------------------------------------------------
inline void Matrix4::initStandOnScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale)
{
	Vector3 yaxis = up                        ; yaxis.Normalize();
	Vector3 zaxis = position - objective      ;
	        zaxis = zaxis - up * zaxis.Dot(up); zaxis.Normalize();
	Vector3 xaxis = yaxis.Cross(zaxis);

	xaxis *= scale;
	yaxis *= scale;
	zaxis *= scale;

	(*this)[0][0] = xaxis.X();
	(*this)[0][1] = yaxis.X();
	(*this)[0][2] = zaxis.X();
	(*this)[0][3] = position.X();
	(*this)[1][0] = xaxis.Y();
	(*this)[1][1] = yaxis.Y();
	(*this)[1][2] = zaxis.Y();
	(*this)[1][3] = position.Y();
	(*this)[2][0] = xaxis.Z();
	(*this)[2][1] = yaxis.Z();
	(*this)[2][2] = zaxis.Z();	
	(*this)[2][3] = position.Z();
	(*this)[3][0] = 0;
	(*this)[3][1] = 0;
	(*this)[3][2] = 0;
	(*this)[3][3] = 1;
}
//----------------------------------------------------------------------------
inline void Matrix4::initPerspective(float w, float h, float n, float f)
{
	initPerspectiveOffCenter(-w/2, w/2, -h/2, h/2, n, f);
}

inline void Matrix4::initPerspectiveFov(float fovY, float aspect, float n, float f)
{
	assert(fovY < Math::ONE_PI);

	float tanHalfFovY = Math::Tan(fovY/2);
	float t = n * tanHalfFovY;
	float r = t * aspect;

	initPerspectiveOffCenter(-r, r, -t, t, n, f);
}

//----------------------------------------------------------------------------
inline void Matrix4::initPerspectiveOffCenter(float l, float r, float b, float t, float n, float f)
{
	m_afEntry[0]  = 2*n  /(r-l);
	m_afEntry[1]  = 0;
	m_afEntry[2]  = (r+l)/(r-l);
	m_afEntry[3]  = 0;

	m_afEntry[4]  = 0;
	m_afEntry[5]  = 2*n  /(t-b);
	m_afEntry[6]  = (t+b)/(t-b);
	m_afEntry[7]  = 0;

	m_afEntry[8]  = 0;
	m_afEntry[9]  = 0;
	m_afEntry[10] = -(f+n)/(f-n);
	m_afEntry[11] = -2*f*n/(f-n);

	m_afEntry[12] = 0;
	m_afEntry[13] = 0;
	m_afEntry[14] = -1;
	m_afEntry[15] = 0;
}

//----------------------------------------------------------------------------
inline void Matrix4::initOrthogonal(float w, float h, float n, float f)
{
	initOrthogonalOffCenter(-w/2, w/2, -h/2, h/2, n, f);
}

//----------------------------------------------------------------------------
inline void Matrix4::initOrthogonalOffCenter(float l, float r, float b, float t, float n, float f)
{
	m_afEntry[0]  =  2    /(r-l);
	m_afEntry[1]  = 0;
	m_afEntry[2]  = 0;
	m_afEntry[3]  = -(r+l)/(r-l);

	m_afEntry[4]  = 0;
	m_afEntry[5]  =  2   /(t-b);
	m_afEntry[6]  = 0;
	m_afEntry[7]  = -(t+b)/(t-b);

	m_afEntry[8]  = 0;
	m_afEntry[9]  = 0;
	m_afEntry[10] = -2    /(f-n);
	m_afEntry[11] = -(f+n)/(f-n);

	m_afEntry[12] = 0;
	m_afEntry[13] = 0;
	m_afEntry[14] = 0;
	m_afEntry[15] = 1;
}

//----------------------------------------------------------------------------
inline Matrix4 operator* (float fScalar, const Matrix4& rkM)
{
    return rkM*fScalar;
}
//----------------------------------------------------------------------------
inline Vector4 operator* (const Vector4& rkV, const Matrix4& rkM)
{
    return Vector4(
        rkV[0]*rkM[0][0]+rkV[1]*rkM[1][0]+rkV[2]*rkM[2][0]+rkV[3]*rkM[3][0],
        rkV[0]*rkM[0][1]+rkV[1]*rkM[1][1]+rkV[2]*rkM[2][1]+rkV[3]*rkM[3][1],
        rkV[0]*rkM[0][2]+rkV[1]*rkM[1][2]+rkV[2]*rkM[2][2]+rkV[3]*rkM[3][2],
        rkV[0]*rkM[0][3]+rkV[1]*rkM[1][3]+rkV[2]*rkM[2][3]+rkV[3]*rkM[3][3]);
}
//----------------------------------------------------------------------------
inline void Matrix4::read(InputStream &is)
{
	for(int i=0; i<16; i++)
		is >> m_afEntry[i];
}
//----------------------------------------------------------------------------
inline void Matrix4::write(OutputStream &os) const
{
	for(int i=0; i<16; i++)
		os << m_afEntry[i];
}
