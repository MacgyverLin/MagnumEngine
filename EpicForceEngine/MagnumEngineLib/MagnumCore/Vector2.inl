///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Vector2::Vector2 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline Vector2::Vector2 (float fX, float fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------
inline Vector2::Vector2 (const float* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
}
//----------------------------------------------------------------------------
inline Vector2::Vector2 (const Vector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------
inline void Vector2::Set(float fX, float fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------
inline Vector2::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline Vector2::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline float Vector2::operator[] (int i) const
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float& Vector2::operator[] (int i)
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float Vector2::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float& Vector2::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float Vector2::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float& Vector2::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline Vector2& Vector2::operator= (const Vector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline int Vector2::CompareArrays (const Vector2& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,2*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Vector2::operator== (const Vector2& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool Vector2::operator!= (const Vector2& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool Vector2::operator< (const Vector2& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool Vector2::operator<= (const Vector2& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool Vector2::operator> (const Vector2& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool Vector2::operator>= (const Vector2& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::operator+ (const Vector2& rkV) const
{
    return Vector2(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::operator- (const Vector2& rkV) const
{
    return Vector2(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::operator* (float fScalar) const
{
    return Vector2(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::operator/ (float fScalar) const
{
    Vector2 kQuot;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_REAL;
        kQuot.m_afTuple[1] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::operator- () const
{
    return Vector2(
        -m_afTuple[0],
        -m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline Vector2 operator* (float fScalar, const Vector2& rkV)
{
    return Vector2(
        fScalar*rkV[0],
        fScalar*rkV[1]);
}
//----------------------------------------------------------------------------
inline Vector2& Vector2::operator+= (const Vector2& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector2& Vector2::operator-= (const Vector2& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector2& Vector2::operator*= (float fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Vector2& Vector2::operator/= (float fScalar)
{
    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_REAL;
        m_afTuple[1] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline float Vector2::Length () const
{
    return Math::Sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline float Vector2::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Vector2::Dot (const Vector2& rkV) const
{
    return
        m_afTuple[0]*rkV.m_afTuple[0] +
        m_afTuple[1]*rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Vector2::Normalize ()
{
    float fLength = Length();

    if (fLength > Math::ZERO_TOLERANCE)
    {
        float fInvLength = ((float)1.0)/fLength;
        m_afTuple[0] *= fInvLength;
        m_afTuple[1] *= fInvLength;
    }
    else
    {
        fLength = (float)0.0;
        m_afTuple[0] = (float)0.0;
        m_afTuple[1] = (float)0.0;
    }

    return fLength;
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::Perp () const
{
    return Vector2(m_afTuple[1],-m_afTuple[0]);
}
//----------------------------------------------------------------------------
inline Vector2 Vector2::UnitPerp () const
{
    Vector2 kPerp(m_afTuple[1],-m_afTuple[0]);
    kPerp.Normalize();
    return kPerp;
}
//----------------------------------------------------------------------------
inline float Vector2::DotPerp (const Vector2& rkV) const
{
    return m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0];
}
//----------------------------------------------------------------------------
inline void Vector2::GetBarycentrics (const Vector2& rkV0,
    const Vector2& rkV1, const Vector2& rkV2, float afBary[3])
    const
{
    // compute the vectors relative to V2 of the triangle
    Vector2 akDiff[3] =
    {
        rkV0 - rkV2,
        rkV1 - rkV2,
        *this - rkV2
    };

    // If the vertices have large magnitude, the linear system of equations
    // for computing barycentric coordinates can be ill-conditioned.  To avoid
    // this, uniformly scale the triangle edges to be of order 1.  The scaling
    // of all differences does not change the barycentric coordinates.
    float fMax = (float)0.0;
    int i;
    for (i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            float fValue = Math::FAbs(akDiff[i][j]);
            if (fValue > fMax)
            {
                fMax = fValue;
            }
        }
    }

    // scale down only large data
    if (fMax > (float)1.0)
    {
        float fInvMax = ((float)1.0)/fMax;
        for (i = 0; i < 3; i++)
        {
            akDiff[i] *= fInvMax;
        }
    }

    float fDet = akDiff[0].DotPerp(akDiff[1]);
    if (Math::FAbs(fDet) > Math::ZERO_TOLERANCE)
    {
        float fInvDet = ((float)1.0)/fDet;
        afBary[0] = akDiff[2].DotPerp(akDiff[1])*fInvDet;
        afBary[1] = akDiff[0].DotPerp(akDiff[2])*fInvDet;
        afBary[2] = (float)1.0 - afBary[0] - afBary[1];
    }
    else
    {
        // The triangle is a sliver.  Determine the longest edge and
        // compute barycentric coordinates with respect to that edge.
        Vector2 kE2 = rkV0 - rkV1;
        float fMaxSqrLength = kE2.SquaredLength();
        int iMaxIndex = 2;
        float fSqrLength = akDiff[1].SquaredLength();
        if (fSqrLength > fMaxSqrLength)
        {
            iMaxIndex = 1;
            fMaxSqrLength = fSqrLength;
        }
        fSqrLength = akDiff[0].SquaredLength();
        if (fSqrLength > fMaxSqrLength)
        {
            iMaxIndex = 0;
            fMaxSqrLength = fSqrLength;
        }

        if (fMaxSqrLength > Math::ZERO_TOLERANCE)
        {
            float fInvSqrLength = ((float)1.0)/fMaxSqrLength;
            if (iMaxIndex == 0)
            {
                // P-V2 = t(V0-V2)
                afBary[0] = akDiff[2].Dot(akDiff[0])*fInvSqrLength;
                afBary[1] = (float)0.0;
                afBary[2] = (float)1.0 - afBary[0];
            }
            else if (iMaxIndex == 1)
            {
                // P-V2 = t(V1-V2)
                afBary[0] = (float)0.0;
                afBary[1] = akDiff[2].Dot(akDiff[1])*fInvSqrLength;
                afBary[2] = (float)1.0 - afBary[1];
            }
            else
            {
                // P-V1 = t(V0-V1)
                akDiff[2] = *this - rkV1;
                afBary[0] = akDiff[2].Dot(kE2)*fInvSqrLength;
                afBary[1] = (float)1.0 - afBary[0];
                afBary[2] = (float)0.0;
            }
        }
        else
        {
            // triangle is a nearly a point, just return equal weights
            afBary[0] = ((float)1.0)/(float)3.0;
            afBary[1] = afBary[0];
            afBary[2] = afBary[0];
        }
    }
}
//----------------------------------------------------------------------------
inline void Vector2::Orthonormalize (Vector2& rkU, Vector2& rkV)
{
    // If the input vectors are v0 and v1, then the Gram-Schmidt
    // orthonormalization produces vectors u0 and u1 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    rkU.Normalize();

    // compute u1
    float fDot0 = rkU.Dot(rkV); 
    rkV -= rkU*fDot0;
    rkV.Normalize();
}
//----------------------------------------------------------------------------
inline void Vector2::GenerateOrthonormalBasis (Vector2& rkU, Vector2& rkV,
    bool bUnitLengthV)
{
    if (!bUnitLengthV)
    {
        rkV.Normalize();
    }

    rkU = rkV.Perp();
}
//----------------------------------------------------------------------------
inline void Vector2::ComputeExtremes (int iVQuantity, const Vector2* akPoint,
    Vector2& rkMin, Vector2& rkMax)
{
    assert(iVQuantity > 0 && akPoint);

    rkMin = akPoint[0];
    rkMax = rkMin;
    for (int i = 1; i < iVQuantity; i++)
    {
        const Vector2& rkPoint = akPoint[i];
        for (int j = 0; j < 2; j++)
        {
            if (rkPoint[j] < rkMin[j])
            {
                rkMin[j] = rkPoint[j];
            }
            else if (rkPoint[j] > rkMax[j])
            {
                rkMax[j] = rkPoint[j];
            }
        }
    }
}
//----------------------------------------------------------------------------
inline void Vector2::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1];
}
//----------------------------------------------------------------------------
inline void Vector2::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1];
}