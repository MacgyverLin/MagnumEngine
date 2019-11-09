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
Cone3::Cone3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Cone3::Cone3 (const Vector3& rkVertex,
    const Vector3& rkAxis, float fAngle)
    :
    Vertex(rkVertex),
    Axis(rkAxis)
{
    CosAngle = Math::Cos(fAngle);
    SinAngle = Math::Sin(fAngle);
}
//----------------------------------------------------------------------------
inline 
Cone3::Cone3 (const Vector3& rkVertex,
    const Vector3& rkAxis, float fCosAngle, float fSinAngle)
    :
    Vertex(rkVertex),
    Axis(rkAxis)
{
    CosAngle = fCosAngle;
    SinAngle = fSinAngle;
}
//----------------------------------------------------------------------------

