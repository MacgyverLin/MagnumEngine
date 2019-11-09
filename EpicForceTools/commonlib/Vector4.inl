///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Vector4::Vector4 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline Vector4::Vector4 (float fX, float fY, float fZ, float fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------
inline Vector4::Vector4 (const float* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
    m_afTuple[3] = afTuple[3];
}
//----------------------------------------------------------------------------
inline Vector4::Vector4 (const Vector4& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void Vector4::Set (float fX, float fY, float fZ, float fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------
inline Vector4::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline Vector4::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline float Vector4::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float& Vector4::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float Vector4::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float& Vector4::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float Vector4::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float& Vector4::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Vector4::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float& Vector4::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float Vector4::W () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float& Vector4::W ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline Vector4& Vector4::operator= (const Vector4& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline int Vector4::CompareArrays (const Vector4& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Vector4::operator== (const Vector4& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool Vector4::operator!= (const Vector4& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool Vector4::operator< (const Vector4& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool Vector4::operator<= (const Vector4& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool Vector4::operator> (const Vector4& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool Vector4::operator>= (const Vector4& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline Vector4 Vector4::operator+ (const Vector4& rkV) const
{
    return Vector4(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1],
        m_afTuple[2]+rkV.m_afTuple[2],
        m_afTuple[3]+rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Vector4 Vector4::operator- (const Vector4& rkV) const
{
    return Vector4(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1],
        m_afTuple[2]-rkV.m_afTuple[2],
        m_afTuple[3]-rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Vector4 Vector4::operator* (float fScalar) const
{
    return Vector4(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2],
        fScalar*m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Vector4 Vector4::operator/ (float fScalar) const
{
    Vector4 kQuot;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
        kQuot.m_afTuple[2] = fInvScalar*m_afTuple[2];
        kQuot.m_afTuple[3] = fInvScalar*m_afTuple[3];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_REAL;
        kQuot.m_afTuple[1] = Math::MAX_REAL;
        kQuot.m_afTuple[2] = Math::MAX_REAL;
        kQuot.m_afTuple[3] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline Vector4 Vector4::operator- () const
{
    return Vector4(
        -m_afTuple[0],
        -m_afTuple[1],
        -m_afTuple[2],
        -m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Vector4 operator* (float fScalar, const Vector4& rkV)
{
    return Vector4(
        fScalar*rkV[0],
        fScalar*rkV[1],
        fScalar*rkV[2],
        fScalar*rkV[3]);
}
//----------------------------------------------------------------------------
inline Vector4& Vector4::operator+= (const Vector4& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    m_afTuple[2] += rkV.m_afTuple[2];
    m_afTuple[3] += rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector4& Vector4::operator-= (const Vector4& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    m_afTuple[2] -= rkV.m_afTuple[2];
    m_afTuple[3] -= rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline Vector4& Vector4::operator*= (float fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    m_afTuple[3] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Vector4& Vector4::operator/= (float fScalar)
{
    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
        m_afTuple[2] *= fInvScalar;
        m_afTuple[3] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_REAL;
        m_afTuple[1] = Math::MAX_REAL;
        m_afTuple[2] = Math::MAX_REAL;
        m_afTuple[3] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline float Vector4::Length () const
{
    return Math::Sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline float Vector4::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float Vector4::Dot (const Vector4& rkV) const
{
    return
        m_afTuple[0]*rkV.m_afTuple[0] +
        m_afTuple[1]*rkV.m_afTuple[1] +
        m_afTuple[2]*rkV.m_afTuple[2] +
        m_afTuple[3]*rkV.m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float Vector4::Normalize ()
{
    float fLength = Length();

    if (fLength > Math::ZERO_TOLERANCE)
    {
        float fInvLength = ((float)1.0)/fLength;
        m_afTuple[0] *= fInvLength;
        m_afTuple[1] *= fInvLength;
        m_afTuple[2] *= fInvLength;
        m_afTuple[3] *= fInvLength;
    }
    else
    {
        fLength = (float)0.0;
        m_afTuple[0] = (float)0.0;
        m_afTuple[1] = (float)0.0;
        m_afTuple[2] = (float)0.0;
        m_afTuple[3] = (float)0.0;
    }

    return fLength;
}
//----------------------------------------------------------------------------
inline void Vector4::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void Vector4::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}