///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline IVector3::IVector3 ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline IVector3::IVector3 (int fX, int fY, int fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------
inline IVector3::IVector3 (const int* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
}
//----------------------------------------------------------------------------
inline IVector3::IVector3 (const IVector3& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
}
//----------------------------------------------------------------------------
inline void IVector3::Set (int fX, int fY, int fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------
inline IVector3::operator const int* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline IVector3::operator int* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline int IVector3::operator[] (int i) const
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int& IVector3::operator[] (int i)
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline int IVector3::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int& IVector3::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline int IVector3::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline int& IVector3::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline int IVector3::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline int& IVector3::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator= (const IVector3& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline int IVector3::CompareArrays (const IVector3& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,3*sizeof(int));
}
//----------------------------------------------------------------------------
inline bool IVector3::operator== (const IVector3& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------
inline bool IVector3::operator!= (const IVector3& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------
inline bool IVector3::operator< (const IVector3& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
inline bool IVector3::operator<= (const IVector3& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
inline bool IVector3::operator> (const IVector3& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
inline bool IVector3::operator>= (const IVector3& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::operator+ (const IVector3& rkV) const
{
    return IVector3(
        m_afTuple[0]+rkV.m_afTuple[0],
        m_afTuple[1]+rkV.m_afTuple[1],
        m_afTuple[2]+rkV.m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::operator- (const IVector3& rkV) const
{
    return IVector3(
        m_afTuple[0]-rkV.m_afTuple[0],
        m_afTuple[1]-rkV.m_afTuple[1],
        m_afTuple[2]-rkV.m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::operator* (int fScalar) const
{
    return IVector3(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::operator/ (int fScalar) const
{
    IVector3 kQuot;

    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        kQuot.m_afTuple[0] = fInvScalar*m_afTuple[0];
        kQuot.m_afTuple[1] = fInvScalar*m_afTuple[1];
        kQuot.m_afTuple[2] = fInvScalar*m_afTuple[2];
    }
    else
    {
        kQuot.m_afTuple[0] = Math::MAX_INT;
        kQuot.m_afTuple[1] = Math::MAX_INT;
        kQuot.m_afTuple[2] = Math::MAX_INT;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::operator- () const
{
    return IVector3(
        -m_afTuple[0],
        -m_afTuple[1],
        -m_afTuple[2]);
}
//----------------------------------------------------------------------------
inline IVector3 operator* (int fScalar, const IVector3& rkV)
{
    return IVector3(
        fScalar*rkV[0],
        fScalar*rkV[1],
        fScalar*rkV[2]);
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator+= (const IVector3& rkV)
{
    m_afTuple[0] += rkV.m_afTuple[0];
    m_afTuple[1] += rkV.m_afTuple[1];
    m_afTuple[2] += rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator-= (const IVector3& rkV)
{
    m_afTuple[0] -= rkV.m_afTuple[0];
    m_afTuple[1] -= rkV.m_afTuple[1];
    m_afTuple[2] -= rkV.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator*= (int fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator/= (int fScalar)
{
    if (fScalar != (int)0.0)
    {
        int fInvScalar = ((int)1.0)/fScalar;
        m_afTuple[0] *= fInvScalar;
        m_afTuple[1] *= fInvScalar;
        m_afTuple[2] *= fInvScalar;
    }
    else
    {
        m_afTuple[0] = Math::MAX_INT;
        m_afTuple[1] = Math::MAX_INT;
        m_afTuple[2] = Math::MAX_INT;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline void IVector3::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2];
}
//----------------------------------------------------------------------------
inline void IVector3::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2];
}