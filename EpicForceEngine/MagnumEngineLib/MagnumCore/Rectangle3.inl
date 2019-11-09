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
Rectangle3::Rectangle3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Rectangle3::Rectangle3 (const Vector3& rkCenter,
    const Vector3* akAxis, const float* afExtent)
    :
    Center(rkCenter)
{
    for (int i = 0; i < 2; i++)
    {
        Axis[i] = akAxis[i];
        Extent[i] = afExtent[i];
    }
}
//----------------------------------------------------------------------------
inline 
Rectangle3::Rectangle3 (const Vector3& rkCenter,
    const Vector3& rkAxis0, const Vector3& rkAxis1,
    float fExtent0, float fExtent1)
    :
    Center(rkCenter)
{
    Axis[0] = rkAxis0;
    Axis[1] = rkAxis1;
    Extent[0] = fExtent0;
    Extent[1] = fExtent1;
}
//----------------------------------------------------------------------------
inline 
void Rectangle3::ComputeVertices (Vector3 akVertex[4]) const
{
    Vector3 akEAxis[2] =
    {
        Extent[0]*Axis[0],
        Extent[1]*Axis[1]
    };

    akVertex[0] = Center - akEAxis[0] - akEAxis[1];
    akVertex[1] = Center + akEAxis[0] - akEAxis[1];
    akVertex[2] = Center + akEAxis[0] + akEAxis[1];
    akVertex[3] = Center - akEAxis[0] + akEAxis[1];
}
//----------------------------------------------------------------------------
inline 
Vector3 Rectangle3::GetPPCorner () const
{
    return Center + Extent[0]*Axis[0] + Extent[1]*Axis[1];
}
//----------------------------------------------------------------------------
inline 
Vector3 Rectangle3::GetPMCorner () const
{
    return Center + Extent[0]*Axis[0] - Extent[1]*Axis[1];
}
//----------------------------------------------------------------------------
inline 
Vector3 Rectangle3::GetMPCorner () const
{
    return Center - Extent[0]*Axis[0] + Extent[1]*Axis[1];
}
//----------------------------------------------------------------------------
inline 
Vector3 Rectangle3::GetMMCorner () const
{
    return Center - Extent[0]*Axis[0] - Extent[1]*Axis[1];
}
//----------------------------------------------------------------------------

