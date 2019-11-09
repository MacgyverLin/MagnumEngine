///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline IVector2::IVector2 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline IVector2::IVector2 (int fX, int fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------
inline IVector2::IVector2 (const int* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
}
//----------------------------------------------------------------------------
inline IVector2::IVector2 (const IVector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------
inline void IVector2::Set(int fX, int fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------
inline IVector2::operator const int* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline IVector2::operator int* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline int IVector2::operator[] (int i) const
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int& IVector2::operator[] (int i)
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int IVector2::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int& IVector2::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int IVector2::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline int& IVector2::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline IVector2& IVector2::operator= (const IVector2& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline int IVector2::CompareArrays (const IVector2& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,2*sizeof(int));
}
//----------------------------------------------------------------------------
inline bool IVector2::operator== (const IVector2& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool IVector2::operator!= (const IVector2& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool IVector2::operator< (const IVector2& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool IVector2::operator<= (const IVector2& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool IVector2::operator> (const IVector2& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool IVector2::operator>= (const IVector2& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline IVector2 IVector2::operator+ (const IVector2& rkV) const
{
    return IVector2(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline IVector2 IVector2::operator- (const IVector2& rkV) const
{
    return IVector2(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline IVector2 IVector2::operator* (int fScalar) const
{
    return IVector2(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline IVector2 IVector2::operator/ (int fScalar) const
{
    IVector2 kQuot;

    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_INT;
        kQuot.m_afTuple[1] = Math::MAX_INT;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline IVector2 IVector2::operator- () const
{
    return IVector2(
        -m_afTuple[0],
        -m_afTuple[1]);
}
//----------------------------------------------------------------------------
inline IVector2 operator* (int fScalar, const IVector2& rkV)
{
    return IVector2(
        fScalar*rkV[0],
        fScalar*rkV[1]);
}
//----------------------------------------------------------------------------
inline IVector2& IVector2::operator+= (const IVector2& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector2& IVector2::operator-= (const IVector2& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector2& IVector2::operator*= (int fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline IVector2& IVector2::operator/= (int fScalar)
{
    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_INT;
        m_afTuple[1] = Math::MAX_INT;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline void IVector2::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1];
}
//----------------------------------------------------------------------------
inline void IVector2::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1];
}