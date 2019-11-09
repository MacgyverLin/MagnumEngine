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
Sphere3::Sphere3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Sphere3::Sphere3 (const Vector3& rkCenter, float fRadius)
    :
    Center(rkCenter),
    Radius(fRadius)
{
}
//----------------------------------------------------------------------------
inline 
Sphere3::Sphere3 (const Sphere3& rkSphere)
    :
    Center(rkSphere.Center),
    Radius(rkSphere.Radius)
{
}
//----------------------------------------------------------------------------
inline 
Sphere3& Sphere3::operator= (const Sphere3& rkSphere)
{
    Center = rkSphere.Center;
    Radius = rkSphere.Radius;
    return *this;
}
//----------------------------------------------------------------------------

