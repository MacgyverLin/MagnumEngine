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
Lozenge3::Lozenge3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Lozenge3::Lozenge3 (const Rectangle3& rkRectangle, float fRadius)
    :
    Rectangle(rkRectangle)
{
    Radius = fRadius;
}
//----------------------------------------------------------------------------

