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
Ray3::Ray3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Ray3::Ray3 (const Vector3& rkOrigin,
    const Vector3& rkDirection)
    :
    Origin(rkOrigin),
    Direction(rkDirection)
{
}
//----------------------------------------------------------------------------

