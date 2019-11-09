///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline 
Segment2::Segment2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Segment2::Segment2 (const Vector2& rkOrigin,
    const Vector2& rkDirection, float fExtent)
    :
    Origin(rkOrigin),
    Direction(rkDirection),
    Extent(fExtent)
{
}
//----------------------------------------------------------------------------
inline 
Vector2 Segment2::GetPosEnd () const
{
    return Origin + Direction*Extent;
}
//----------------------------------------------------------------------------
inline 
Vector2 Segment2::GetNegEnd () const
{
    return Origin - Direction*Extent;
}
//----------------------------------------------------------------------------

