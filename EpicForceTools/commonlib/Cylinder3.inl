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

