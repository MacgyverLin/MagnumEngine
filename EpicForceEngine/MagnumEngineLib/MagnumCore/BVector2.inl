///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
inline BVector2::operator bool* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline bool BVector2::operator[] (int i) const
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool& BVector2::operator[] (int i)
{
    assert(0 <= i && i <= 1);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool BVector2::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool& BVector2::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool BVector2::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline bool& BVector2::Y ()
{
    return m_afTuple[1];
}

inline void BVector2::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1];
}

inline void BVector2::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1];
}