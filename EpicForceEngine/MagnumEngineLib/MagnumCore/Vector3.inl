///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Vector3::Vector3 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline Vector3::Vector3 (float fX, float fY, float fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------
inline Vector3::Vector3 (const float* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
}
//----------------------------------------------------------------------------
inline Vector3::Vector3 (const Vector3& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
}
//----------------------------------------------------------------------------
inline void Vector3::Set (float fX, float fY, float fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------
inline Vector3::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline Vector3::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline float Vector3::operator[] (int i) const
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float& Vector3::operator[] (int i)
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float Vector3::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float& Vector3::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float Vector3::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float& Vector3::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Vector3::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float& Vector3::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator= (const Vector3& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline int Vector3::CompareArrays (const Vector3& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,3*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Vector3::operator== (const Vector3& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool Vector3::operator!= (const Vector3& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool Vector3::operator< (const Vector3& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool Vector3::operator<= (const Vector3& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool Vector3::operator> (const Vector3& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool Vector3::operator>= (const Vector3& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::operator+ (const Vector3& rkV) const
{
    return Vector3(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1],
        m_afTuple[2]+rkV.m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::operator- (const Vector3& rkV) const
{
    return Vector3(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1],
        m_afTuple[2]-rkV.m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::operator* (const Vector3& rkV) const
{
    return Vector3(rkV.m_afTuple[0] * m_afTuple[0],
				   rkV.m_afTuple[1] * m_afTuple[1],
				   rkV.m_afTuple[2] * m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::operator* (float fScalar) const
{
    return Vector3(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2]);
}

//----------------------------------------------------------------------------
inline Vector3 Vector3::operator/ (float fScalar) const
{
    Vector3 kQuot;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
        kQuot.m_afTuple[2] = fInvScalar*m_afTuple[2];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_REAL;
        kQuot.m_afTuple[1] = Math::MAX_REAL;
        kQuot.m_afTuple[2] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::operator- () const
{
    return Vector3(
        -m_afTuple[0],
        -m_afTuple[1],
        -m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline Vector3 operator* (float fScalar, const Vector3& rkV)
{
    return Vector3(
        fScalar*rkV[0],
        fScalar*rkV[1],
        fScalar*rkV[2]);
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator+= (const Vector3& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    m_afTuple[2] += rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator-= (const Vector3& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    m_afTuple[2] -= rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator*= (const Vector3& rkV)
{
    m_afTuple[0] *= rkV.m_afTuple[0];
    m_afTuple[1] *= rkV.m_afTuple[1];
    m_afTuple[2] *= rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator*= (float fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Vector3& Vector3::operator/= (float fScalar)
{
    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
        m_afTuple[2] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_REAL;
        m_afTuple[1] = Math::MAX_REAL;
        m_afTuple[2] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline float Vector3::Length () const
{
    return Math::Sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline float Vector3::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float Vector3::Dot (const Vector3& rkV) const
{
    return
        m_afTuple[0]*rkV.m_afTuple[0] +
        m_afTuple[1]*rkV.m_afTuple[1] +
        m_afTuple[2]*rkV.m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float Vector3::Normalize ()
{
    float fLength = Length();

    if (fLength > Math::ZERO_TOLERANCE)
    {
        float fInvLength = ((float)1.0)/fLength;
        m_afTuple[0] *= fInvLength;
        m_afTuple[1] *= fInvLength;
        m_afTuple[2] *= fInvLength;
    }
    else
    {
        fLength = (float)0.0;
        m_afTuple[0] = (float)0.0;
        m_afTuple[1] = (float)0.0;
        m_afTuple[2] = (float)0.0;
    }

    return fLength;
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::Cross (const Vector3& rkV) const
{
    return Vector3(
        m_afTuple[1]*rkV.m_afTuple[2] - m_afTuple[2]*rkV.m_afTuple[1],
        m_afTuple[2]*rkV.m_afTuple[0] - m_afTuple[0]*rkV.m_afTuple[2],
        m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0]);
}
//----------------------------------------------------------------------------
inline Vector3 Vector3::UnitCross (const Vector3& rkV) const
{
    Vector3 kCross(
        m_afTuple[1]*rkV.m_afTuple[2] - m_afTuple[2]*rkV.m_afTuple[1],
        m_afTuple[2]*rkV.m_afTuple[0] - m_afTuple[0]*rkV.m_afTuple[2],
        m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0]);
    kCross.Normalize();
    return kCross;
}
//----------------------------------------------------------------------------
inline void Vector3::GetBarycentrics (const Vector3& rkV0,
    const Vector3& rkV1, const Vector3& rkV2,
    const Vector3& rkV3, float afBary[4]) const
{
    // compute the vectors relative to V3 of the tetrahedron
    Vector3 akDiff[4] =
    {
        rkV0 - rkV3,
        rkV1 - rkV3,
        rkV2 - rkV3,
        *this - rkV3
    };

    // If the vertices have large magnitude, the linear system of
    // equations for computing barycentric coordinates can be
    // ill-conditioned.  To avoid this, uniformly scale the tetrahedron
    // edges to be of order 1.  The scaling of all differences does not
    // change the barycentric coordinates.
    float fMax = (float)0.0;
    int i;
    for (i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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
        for (i = 0; i < 4; i++)
        {
            akDiff[i] *= fInvMax;
        }
    }

    float fDet = akDiff[0].Dot(akDiff[1].Cross(akDiff[2]));
    Vector3 kE1cE2 = akDiff[1].Cross(akDiff[2]);
    Vector3 kE2cE0 = akDiff[2].Cross(akDiff[0]);
    Vector3 kE0cE1 = akDiff[0].Cross(akDiff[1]);
    if (Math::FAbs(fDet) > Math::ZERO_TOLERANCE)
    {
        float fInvDet = ((float)1.0)/fDet;
        afBary[0] = akDiff[3].Dot(kE1cE2)*fInvDet;
        afBary[1] = akDiff[3].Dot(kE2cE0)*fInvDet;
        afBary[2] = akDiff[3].Dot(kE0cE1)*fInvDet;
        afBary[3] = (float)1.0 - afBary[0] - afBary[1] - afBary[2];
    }
    else
    {
        // The tetrahedron is potentially flat.  Determine the face of
        // maximum area and compute barycentric coordinates with respect
        // to that face.
        Vector3 kE02 = rkV0 - rkV2;
        Vector3 kE12 = rkV1 - rkV2;
        Vector3 kE02cE12 = kE02.Cross(kE12);
        float fMaxSqrArea = kE02cE12.SquaredLength();
        int iMaxIndex = 3;
        float fSqrArea = kE0cE1.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 0;
            fMaxSqrArea = fSqrArea;
        }
        fSqrArea = kE1cE2.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 1;
            fMaxSqrArea = fSqrArea;
        }
        fSqrArea = kE2cE0.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 2;
            fMaxSqrArea = fSqrArea;
        }

        if (fMaxSqrArea > Math::ZERO_TOLERANCE)
        {
            float fInvSqrArea = ((float)1.0)/fMaxSqrArea;
            Vector3 kTmp;
            if (iMaxIndex == 0)
            {
                kTmp = akDiff[3].Cross(akDiff[1]);
                afBary[0] = kE0cE1.Dot(kTmp)*fInvSqrArea;
                kTmp = akDiff[0].Cross(akDiff[3]);
                afBary[1] = kE0cE1.Dot(kTmp)*fInvSqrArea;
                afBary[2] = (float)0.0;
                afBary[3] = (float)1.0 - afBary[0] - afBary[1];
            }
            else if (iMaxIndex == 1)
            {
                afBary[0] = (float)0.0;
                kTmp = akDiff[3].Cross(akDiff[2]);
                afBary[1] = kE1cE2.Dot(kTmp)*fInvSqrArea;
                kTmp = akDiff[1].Cross(akDiff[3]);
                afBary[2] = kE1cE2.Dot(kTmp)*fInvSqrArea;
                afBary[3] = (float)1.0 - afBary[1] - afBary[2];
            }
            else if (iMaxIndex == 2)
            {
                kTmp = akDiff[2].Cross(akDiff[3]);
                afBary[0] = kE2cE0.Dot(kTmp)*fInvSqrArea;
                afBary[1] = (float)0.0;
                kTmp = akDiff[3].Cross(akDiff[0]);
                afBary[2] = kE2cE0.Dot(kTmp)*fInvSqrArea;
                afBary[3] = (float)1.0 - afBary[0] - afBary[2];
            }
            else
            {
                akDiff[3] = *this - rkV2;
                kTmp = akDiff[3].Cross(kE12);
                afBary[0] = kE02cE12.Dot(kTmp)*fInvSqrArea;
                kTmp = kE02.Cross(akDiff[3]);
                afBary[1] = kE02cE12.Dot(kTmp)*fInvSqrArea;
                afBary[2] = (float)1.0 - afBary[0] - afBary[1];
                afBary[3] = (float)0.0;
            }
        }
        else
        {
            // The tetrahedron is potentially a sliver.  Determine the edge of
            // maximum length and compute barycentric coordinates with respect
            // to that edge.
            float fMaxSqrLength = akDiff[0].SquaredLength();
            iMaxIndex = 0;  // <V0,V3>
            float fSqrLength = akDiff[1].SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 1;  // <V1,V3>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = akDiff[2].SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 2;  // <V2,V3>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = kE02.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 3;  // <V0,V2>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = kE12.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 4;  // <V1,V2>
                fMaxSqrLength = fSqrLength;
            }
            Vector3 kE01 = rkV0 - rkV1;
            fSqrLength = kE01.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 5;  // <V0,V1>
                fMaxSqrLength = fSqrLength;
            }

            if (fMaxSqrLength > Math::ZERO_TOLERANCE)
            {
                float fInvSqrLength = ((float)1.0)/fMaxSqrLength;
                if (iMaxIndex == 0)
                {
                    // P-V3 = t*(V0-V3)
                    afBary[0] = akDiff[3].Dot(akDiff[0])*fInvSqrLength;
                    afBary[1] = (float)0.0;
                    afBary[2] = (float)0.0;
                    afBary[3] = (float)1.0 - afBary[0];
                }
                else if (iMaxIndex == 1)
                {
                    // P-V3 = t*(V1-V3)
                    afBary[0] = (float)0.0;
                    afBary[1] = akDiff[3].Dot(akDiff[1])*fInvSqrLength;
                    afBary[2] = (float)0.0;
                    afBary[3] = (float)1.0 - afBary[1];
                }
                else if (iMaxIndex == 2)
                {
                    // P-V3 = t*(V2-V3)
                    afBary[0] = (float)0.0;
                    afBary[1] = (float)0.0;
                    afBary[2] = akDiff[3].Dot(akDiff[2])*fInvSqrLength;
                    afBary[3] = (float)1.0 - afBary[2];
                }
                else if (iMaxIndex == 3)
                {
                    // P-V2 = t*(V0-V2)
                    akDiff[3] = *this - rkV2;
                    afBary[0] = akDiff[3].Dot(kE02)*fInvSqrLength;
                    afBary[1] = (float)0.0;
                    afBary[2] = (float)1.0 - afBary[0];
                    afBary[3] = (float)0.0;
                }
                else if (iMaxIndex == 4)
                {
                    // P-V2 = t*(V1-V2)
                    akDiff[3] = *this - rkV2;
                    afBary[0] = (float)0.0;
                    afBary[1] = akDiff[3].Dot(kE12)*fInvSqrLength;
                    afBary[2] = (float)1.0 - afBary[1];
                    afBary[3] = (float)0.0;
                }
                else
                {
                    // P-V1 = t*(V0-V1)
                    akDiff[3] = *this - rkV1;
                    afBary[0] = akDiff[3].Dot(kE01)*fInvSqrLength;
                    afBary[1] = (float)1.0 - afBary[0];
                    afBary[2] = (float)0.0;
                    afBary[3] = (float)0.0;
                }
            }
            else
            {
                // tetrahedron is a nearly a point, just return equal weights
                afBary[0] = (float)0.25;
                afBary[1] = afBary[0];
                afBary[2] = afBary[0];
                afBary[3] = afBary[0];
            }
        }
    }
}
//----------------------------------------------------------------------------
inline void Vector3::Orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW)
{
    // If the input vectors are v0, v1, and v2, then the Gram-Schmidt
    // orthonormalization produces vectors u0, u1, and u2 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    rkU.Normalize();

    // compute u1
    float fDot0 = rkU.Dot(rkV); 
    rkV -= fDot0*rkU;
    rkV.Normalize();

    // compute u2
    float fDot1 = rkV.Dot(rkW);
    fDot0 = rkU.Dot(rkW);
    rkW -= fDot0*rkU + fDot1*rkV;
    rkW.Normalize();
}
//----------------------------------------------------------------------------
inline void Vector3::Orthonormalize (Vector3* akV)
{
    Orthonormalize(akV[0],akV[1],akV[2]);
}
//----------------------------------------------------------------------------
inline void Vector3::GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
    Vector3& rkW, bool bUnitLengthW)
{
    if (!bUnitLengthW)
    {
        rkW.Normalize();
    }

    float fInvLength;

    if (Math::FAbs(rkW.m_afTuple[0]) >=
        Math::FAbs(rkW.m_afTuple[1]) )
    {
        // W.x or W.z is the largest magnitude component, swap them
        fInvLength = Math::InvSqrt(rkW.m_afTuple[0]*rkW.m_afTuple[0] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = -rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[1] = (float)0.0;
        rkU.m_afTuple[2] = +rkW.m_afTuple[0]*fInvLength;
        rkV.m_afTuple[0] = rkW.m_afTuple[1]*rkU.m_afTuple[2];
        rkV.m_afTuple[1] = rkW.m_afTuple[2]*rkU.m_afTuple[0] -
            rkW.m_afTuple[0]*rkU.m_afTuple[2];
        rkV.m_afTuple[2] = -rkW.m_afTuple[1]*rkU.m_afTuple[0];
    }
    else
    {
        // W.y or W.z is the largest magnitude component, swap them
        fInvLength = Math::InvSqrt(rkW.m_afTuple[1]*rkW.m_afTuple[1] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = (float)0.0;
        rkU.m_afTuple[1] = +rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[2] = -rkW.m_afTuple[1]*fInvLength;
        rkV.m_afTuple[0] = rkW.m_afTuple[1]*rkU.m_afTuple[2] -
            rkW.m_afTuple[2]*rkU.m_afTuple[1];
        rkV.m_afTuple[1] = -rkW.m_afTuple[0]*rkU.m_afTuple[2];
        rkV.m_afTuple[2] = rkW.m_afTuple[0]*rkU.m_afTuple[1];
    }
}
//----------------------------------------------------------------------------
inline void Vector3::ComputeExtremes (int iVQuantity, const Vector3* akPoint,
    Vector3& rkMin, Vector3& rkMax)
{
    assert(iVQuantity > 0 && akPoint);

    rkMin = akPoint[0];
    rkMax = rkMin;
    for (int i = 1; i < iVQuantity; i++)
    {
        const Vector3& rkPoint = akPoint[i];
        for (int j = 0; j < 3; j++)
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
inline void Vector3::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2];
}
//----------------------------------------------------------------------------
inline void Vector3::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2];
}