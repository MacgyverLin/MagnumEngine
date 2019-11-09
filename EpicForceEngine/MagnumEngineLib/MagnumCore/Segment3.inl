///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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

