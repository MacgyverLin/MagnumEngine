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
Circle3::Circle3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Circle3::Circle3 (const Vector3& rkCenter,
    const Vector3& rkU, const Vector3& rkV,
    const Vector3& rkN, float fRadius)
    :
    Center(rkCenter),
    U(rkU),
    V(rkV),
    N(rkN)
{
    Radius = fRadius;
}
//----------------------------------------------------------------------------

