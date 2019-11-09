inline BVector3::operator const bool* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline BVector3::operator bool* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline bool BVector3::operator[] (int i) const
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool& BVector3::operator[] (int i)
{
    assert(0 <= i && i <= 2);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline bool BVector3::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool& BVector3::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline bool BVector3::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline bool& BVector3::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline bool BVector3::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline bool& BVector3::Z ()
{
    return m_afTuple[2];
}

inline void BVector3::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2];
}

inline void BVector3::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2];
}