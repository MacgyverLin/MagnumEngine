///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Rectangle2::Rectangle2 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline Rectangle2::Rectangle2 (float fX, float fY, float fWidth, float fHeight)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fWidth;
    m_afTuple[3] = fHeight;
}
//----------------------------------------------------------------------------
inline Rectangle2::Rectangle2 (const float* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
    m_afTuple[3] = afTuple[3];
}
//----------------------------------------------------------------------------
inline Rectangle2::Rectangle2 (const Rectangle2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void Rectangle2::Set (float fX, float fY, float fWidth, float fHeight)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fWidth;
    m_afTuple[3] = fHeight;
}
//----------------------------------------------------------------------------
inline Rectangle2::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline Rectangle2::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline float Rectangle2::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float& Rectangle2::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float Rectangle2::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float& Rectangle2::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float Rectangle2::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float& Rectangle2::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Rectangle2::Width () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float& Rectangle2::Width ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float Rectangle2::Height () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float& Rectangle2::Height ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline Rectangle2& Rectangle2::operator= (const Rectangle2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline int Rectangle2::CompareArrays (const Rectangle2& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator== (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator!= (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator< (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator<= (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator> (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool Rectangle2::operator>= (const Rectangle2& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline Rectangle2 Rectangle2::operator+ (const Rectangle2& rkV) const
{
    return Rectangle2(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1],
        m_afTuple[2]+rkV.m_afTuple[2],
        m_afTuple[3]+rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Rectangle2 Rectangle2::operator- (const Rectangle2& rkV) const
{
    return Rectangle2(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1],
        m_afTuple[2]-rkV.m_afTuple[2],
        m_afTuple[3]-rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Rectangle2 Rectangle2::operator* (float fScalar) const
{
    return Rectangle2(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2],
        fScalar*m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Rectangle2 Rectangle2::operator/ (float fScalar) const
{
    Rectangle2 kQuot;

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
inline Rectangle2 Rectangle2::operator- () const
{
    return Rectangle2(
        -m_afTuple[0],
        -m_afTuple[1],
        -m_afTuple[2],
        -m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Rectangle2 operator* (float fScalar, const Rectangle2& rkV)
{
    return Rectangle2(
        fScalar*rkV[0],
        fScalar*rkV[1],
        fScalar*rkV[2],
        fScalar*rkV[3]);
}
//----------------------------------------------------------------------------
inline Rectangle2& Rectangle2::operator+= (const Rectangle2& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    m_afTuple[2] += rkV.m_afTuple[2];
    m_afTuple[3] += rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline Rectangle2& Rectangle2::operator-= (const Rectangle2& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    m_afTuple[2] -= rkV.m_afTuple[2];
    m_afTuple[3] -= rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline Rectangle2& Rectangle2::operator*= (float fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    m_afTuple[3] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline Rectangle2& Rectangle2::operator/= (float fScalar)
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
inline void Rectangle2::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void Rectangle2::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}