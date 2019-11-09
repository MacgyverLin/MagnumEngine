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

