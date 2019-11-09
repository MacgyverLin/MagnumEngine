///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline IVector4::IVector4 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline IVector4::IVector4 (int fX, int fY, int fZ, int fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------
inline IVector4::IVector4 (const int* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
    m_afTuple[3] = afTuple[3];
}
//----------------------------------------------------------------------------
inline IVector4::IVector4 (const IVector4& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void IVector4::Set (int fX, int fY, int fZ, int fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------
inline IVector4::operator const int* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline IVector4::operator int* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline int IVector4::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int& IVector4::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int IVector4::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int& IVector4::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int IVector4::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline int& IVector4::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline int IVector4::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline int& IVector4::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline int IVector4::W () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline int& IVector4::W ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline IVector4& IVector4::operator= (const IVector4& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline int IVector4::CompareArrays (const IVector4& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,4*sizeof(int));
}
//----------------------------------------------------------------------------
inline bool IVector4::operator== (const IVector4& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool IVector4::operator!= (const IVector4& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool IVector4::operator< (const IVector4& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool IVector4::operator<= (const IVector4& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool IVector4::operator> (const IVector4& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool IVector4::operator>= (const IVector4& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline IVector4 IVector4::operator+ (const IVector4& rkV) const
{
    return IVector4(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1],
        m_afTuple[2]+rkV.m_afTuple[2],
        m_afTuple[3]+rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline IVector4 IVector4::operator- (const IVector4& rkV) const
{
    return IVector4(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1],
        m_afTuple[2]-rkV.m_afTuple[2],
        m_afTuple[3]-rkV.m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline IVector4 IVector4::operator* (int fScalar) const
{
    return IVector4(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2],
        fScalar*m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline IVector4 IVector4::operator/ (int fScalar) const
{
    IVector4 kQuot;

    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
        kQuot.m_afTuple[2] = fInvScalar*m_afTuple[2];
        kQuot.m_afTuple[3] = fInvScalar*m_afTuple[3];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_INT;
        kQuot.m_afTuple[1] = Math::MAX_INT;
        kQuot.m_afTuple[2] = Math::MAX_INT;
        kQuot.m_afTuple[3] = Math::MAX_INT;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline IVector4 IVector4::operator- () const
{
    return IVector4(
        -m_afTuple[0],
        -m_afTuple[1],
        -m_afTuple[2],
        -m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline IVector4 operator* (int fScalar, const IVector4& rkV)
{
    return IVector4(
        fScalar*rkV[0],
        fScalar*rkV[1],
        fScalar*rkV[2],
        fScalar*rkV[3]);
}
//----------------------------------------------------------------------------
inline IVector4& IVector4::operator+= (const IVector4& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    m_afTuple[2] += rkV.m_afTuple[2];
    m_afTuple[3] += rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector4& IVector4::operator-= (const IVector4& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    m_afTuple[2] -= rkV.m_afTuple[2];
    m_afTuple[3] -= rkV.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector4& IVector4::operator*= (int fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    m_afTuple[3] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline IVector4& IVector4::operator/= (int fScalar)
{
    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
        m_afTuple[2] *= fInvScalar;
        m_afTuple[3] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_INT;
        m_afTuple[1] = Math::MAX_INT;
        m_afTuple[2] = Math::MAX_INT;
        m_afTuple[3] = Math::MAX_INT;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline void IVector4::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void IVector4::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}