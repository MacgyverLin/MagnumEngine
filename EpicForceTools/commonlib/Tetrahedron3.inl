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
Tetrahedron3::Tetrahedron3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline 
Tetrahedron3::Tetrahedron3 (const Vector3& rkV0,
    const Vector3& rkV1, const Vector3& rkV2,
    const Vector3& rkV3)
{
    V[0] = rkV0;
    V[1] = rkV1;
    V[2] = rkV2;
    V[3] = rkV3;
}
//----------------------------------------------------------------------------
inline 
Tetrahedron3::Tetrahedron3 (const Vector3 akV[4])
{
    size_t uiSize = 4*sizeof(Vector3);
    System::Memcpy(V, akV, uiSize);
}
//----------------------------------------------------------------------------
inline 
void Tetrahedron3::GetFaceIndices (int iFace, int aiIndex[3]) const
{
    switch (iFace)
    {
    case 0:
        aiIndex[0] = 0;  aiIndex[1] = 2;  aiIndex[2] = 1;
        break;
    case 1:
        aiIndex[0] = 0;  aiIndex[1] = 1;  aiIndex[2] = 3;
        break;
    case 2:
        aiIndex[0] = 0;  aiIndex[1] = 3;  aiIndex[2] = 2;
        break;
    case 3:
        aiIndex[0] = 1;  aiIndex[1] = 2;  aiIndex[2] = 3;
        break;
    default:
        assert(false);
        break;
    }
}
//----------------------------------------------------------------------------
inline 
void Tetrahedron3::GetPlanes (Plane3 akPlane[4],
    bool bUnitLengthNormals) const
{
    Vector3 kEdge10 = V[1] - V[0];
    Vector3 kEdge20 = V[2] - V[0];
    Vector3 kEdge30 = V[3] - V[0];
    Vector3 kEdge21 = V[2] - V[1];
    Vector3 kEdge31 = V[3] - V[1];

    if (bUnitLengthNormals)
    {
        akPlane[0].Normal = kEdge20.UnitCross(kEdge10);  // <v0,v2,v1>
        akPlane[1].Normal = kEdge10.UnitCross(kEdge30);  // <v0,v1,v3>
        akPlane[2].Normal = kEdge30.UnitCross(kEdge20);  // <v0,v3,v2>
        akPlane[3].Normal = kEdge21.UnitCross(kEdge31);  // <v1,v2,v3>
    }
    else
    {
        akPlane[0].Normal = kEdge20.Cross(kEdge10);  // <v0,v2,v1>
        akPlane[1].Normal = kEdge10.Cross(kEdge30);  // <v0,v1,v3>
        akPlane[2].Normal = kEdge30.Cross(kEdge20);  // <v0,v3,v2>
        akPlane[3].Normal = kEdge21.Cross(kEdge31);  // <v1,v2,v3>
    }

    float fDet = kEdge10.Dot(akPlane[3].Normal);
    int i;
    if (fDet < (float)0.0)
    {
        // normals are inner pointing, reverse their directions
        for (i = 0; i < 4; i++)
        {
            akPlane[i].Normal = -akPlane[i].Normal;
        }
    }

    for (i = 0; i < 4; i++)
    {
        akPlane[i].Constant = V[i].Dot(akPlane[i].Normal);
    }
}
//----------------------------------------------------------------------------

