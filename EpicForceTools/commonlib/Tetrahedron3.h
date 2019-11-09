///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Tetrahedron3_h_
#define _Tetrahedron3_h_

#include "Stage.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Plane3.h"

namespace EpicForce
{

class Tetrahedron3
{
public:
    // The vertices are ordered so that the triangular faces are
    // counterclockwise when viewed by an observer outside the tetrahedron:
    //   face 0 = <V[0],V[2],V[1]>
    //   face 1 = <V[0],V[1],V[3]>
    //   face 2 = <V[0],V[3],V[2]>
    //   face 3 = <V[1],V[2],V[3]>

    // Construction.
    Tetrahedron3 ();  // uninitialized
    Tetrahedron3 (const Vector3& rkV0, const Vector3& rkV1,
        const Vector3& rkV2, const Vector3& rkV3);
    Tetrahedron3 (const Vector3 akV[4]);

    // Get the vertex indices for the specified face.
    void GetFaceIndices (int iFace, int aiIndex[3]) const;

    // Construct the planes of the faces.  The planes have outer pointing
    // normal vectors.  The normals may be specified to be unit length.  The
    // plane indexing is the same as the face indexing mentioned previously.
    void GetPlanes (Plane3 akPlane[4], bool bUnitLengthNormals) const;

    Vector3 V[4];
};

#include "Tetrahedron3.inl"

}

#endif

