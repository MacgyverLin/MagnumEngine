///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Polyhedron3_h_
#define _Polyhedron3_h_

#include "Stage.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"

namespace Magnum
{


class Polyhedron3
{
public:
    // Construction and destruction.  The caller is responsible for ensuring
    // that the mesh represents a simple polyhedron (2-manifold with the
    // topology of a sphere, non-self-intersecting).  The triangular faces
    // must be orderd counterclockwise when viewed from outside the mesh.
    // To assign Polyhedron3 the ownership of the input arrays, set bOwner to
    // 'true'; otherwise, set it to 'false', in which case the caller is
    // responsible for deleting the arrays if they were dynamically allocated.
    Polyhedron3 (int iVQuantity, Vector3* akVertex, int iTQuantity,
        int* aiIndex, bool bOwner);

    // Copy constructor.  If the input polyhedron owns its data, then a copy
    // is made for 'this' object, in which case 'this' owns its data.  If the
    // input polyhedron does not own its data, 'this' shares that same data
    // so does not own it.
    Polyhedron3 (const Polyhedron3& rkPoly);

    virtual ~Polyhedron3 ();

    // Assignment.  If the input polyhedron owns its data, then a copy is
    // made for 'this' object, in which case 'this' owns its data.  If the
    // input polyhedron does not own its data, 'this' shares that same data
    // so does not own it.
    Polyhedron3& operator= (const Polyhedron3& rkPoly);

    // read-only member access
    int GetVQuantity () const;
    const Vector3* GetVertices () const;
    const Vector3& GetVertex (int i) const;
    int GetTQuantity () const;
    const int* GetIndices () const;
    const int* GetTriangle (int i) const;

    // Allow vertex modification.  No guarantee is made that the mesh will
    // remain non-self-intersecting.
    virtual void SetVertex (int i, const Vector3& rkV);
    Vector3* GetVertices ();

    // Compute various information about the polyhedron.
    Vector3 ComputeVertexAverage () const;
    float ComputeSurfaceArea () const;
    float ComputeVolume () const;

protected:
    int m_iVQuantity;
    Vector3* m_akVertex;
    int m_iTQuantity;
    int* m_aiIndex;
    bool m_bOwner;
};

#include "Polyhedron3.inl"

}

#endif

