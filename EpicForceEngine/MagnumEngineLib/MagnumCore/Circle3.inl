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

