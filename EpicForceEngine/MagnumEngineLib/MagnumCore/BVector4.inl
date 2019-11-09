inline BVector4::operator const bool* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline BVector4::operator bool* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline bool BVector4::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool& BVector4::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool BVector4::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool& BVector4::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool BVector4::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline bool& BVector4::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline bool BVector4::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline bool& BVector4::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline bool BVector4::W () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline bool& BVector4::W ()
{
    return m_afTuple[3];
}

inline void BVector4::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}

inline void BVector4::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}