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
Line2::Line2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Line2::Line2 (const Vector2& rkOrigin,
    const Vector2& rkDirection)
    :
    Origin(rkOrigin),
    Direction(rkDirection)
{
}
//----------------------------------------------------------------------------

