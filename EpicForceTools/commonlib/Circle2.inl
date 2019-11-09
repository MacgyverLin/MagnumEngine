///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Circle2::Circle2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline Circle2::Circle2 (const Vector2& rkCenter, float fRadius)
    :
    Center(rkCenter)
{
    Radius = fRadius;
}
//----------------------------------------------------------------------------

