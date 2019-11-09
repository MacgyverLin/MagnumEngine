///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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

