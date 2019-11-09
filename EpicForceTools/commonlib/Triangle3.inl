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
Triangle3::Triangle3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Triangle3::Triangle3 (const Vector3& rkV0,
    const Vector3& rkV1, const Vector3& rkV2)
{
    V[0] = rkV0;
    V[1] = rkV1;
    V[2] = rkV2;
}
//----------------------------------------------------------------------------
inline 
Triangle3::Triangle3 (const Vector3 akV[3])
{
    for (int i = 0; i < 3; i++)
        V[i] = akV[i];
}
//----------------------------------------------------------------------------

