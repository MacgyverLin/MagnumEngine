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
Cylinder3::Cylinder3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Cylinder3::Cylinder3 (const Segment3& rkSegment, float fHeight,
    float fRadius)
    :
    Segment(rkSegment)
{
    Height = fHeight;
    Radius = fRadius;
}
//----------------------------------------------------------------------------

