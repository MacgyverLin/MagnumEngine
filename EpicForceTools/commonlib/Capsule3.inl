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
Capsule3::Capsule3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Capsule3::Capsule3 (const Segment3& rkSegment, float fRadius)
    :
    Segment(rkSegment)
{
    Radius = fRadius;
}
//----------------------------------------------------------------------------

