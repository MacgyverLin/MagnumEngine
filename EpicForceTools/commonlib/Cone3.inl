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

