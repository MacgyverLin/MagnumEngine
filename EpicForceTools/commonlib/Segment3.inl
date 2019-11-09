///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Segment3::Segment3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline Segment3::Segment3 (const Vector3& rkOrigin,
    const Vector3& rkDirection, float fExtent)
    :
    Origin(rkOrigin),
    Direction(rkDirection),
    Extent(fExtent)
{
}
//----------------------------------------------------------------------------
inline Vector3 Segment3::GetPosEnd () const
{
    return Origin + Extent*Direction;
}
//----------------------------------------------------------------------------
inline Vector3 Segment3::GetNegEnd () const
{
    return Origin - Extent*Direction;
}
//----------------------------------------------------------------------------

