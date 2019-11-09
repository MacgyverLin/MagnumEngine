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
Polyhedron3::Polyhedron3 (int iVQuantity, Vector3* akVertex,
    int iTQuantity, int* aiIndex, bool bOwner)
{
    // The polyhedron must be at least a tetrahedron.
    assert(iVQuantity >= 4 && akVertex);
    assert(iTQuantity >= 4 && aiIndex);

    m_iVQuantity = iVQuantity;
    m_akVertex = akVertex;
    m_iTQuantity = iTQuantity;
    m_aiIndex = aiIndex;
    m_bOwner = bOwner;
}
//----------------------------------------------------------------------------
inline 
Polyhedron3::Polyhedron3 (const Polyhedron3& rkPoly)
{
    m_akVertex = 0;
    m_aiIndex = 0;
    m_bOwner = false;
    *this = rkPoly;
}
//----------------------------------------------------------------------------
inline 
Polyhedron3::~Polyhedron3 ()
{
    if (m_bOwner)
    {
        delete[] m_akVertex;
        delete[] m_aiIndex;
    }
}
//----------------------------------------------------------------------------
inline 
Polyhedron3& Polyhedron3::operator= (const Polyhedron3& rkPoly)
{
    if (m_bOwner)
    {
        delete[] m_akVertex;
        delete[] m_aiIndex;
    }

    m_iVQuantity = rkPoly.m_iVQuantity;
    m_iTQuantity = rkPoly.m_iTQuantity;
    m_bOwner = rkPoly.m_bOwner;

    if (m_bOwner)
    {
        m_akVertex = new Vector3[m_iVQuantity];
        size_t uiSize = m_iVQuantity*sizeof(Vector3);
        System::Memcpy(m_akVertex,rkPoly.m_akVertex,uiSize);
        m_aiIndex = new int[3*m_iTQuantity];
        uiSize = 3*m_iTQuantity*sizeof(int);
        System::Memcpy(m_aiIndex,rkPoly.m_aiIndex,uiSize);
    }
    else
    {
        m_akVertex = rkPoly.m_akVertex;
        m_aiIndex = rkPoly.m_aiIndex;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline 
int Polyhedron3::GetVQuantity () const
{
    return m_iVQuantity;
}
//----------------------------------------------------------------------------
inline 
const Vector3* Polyhedron3::GetVertices () const
{
    return m_akVertex;
}
//----------------------------------------------------------------------------
inline 
const Vector3& Polyhedron3::GetVertex (int i) const
{
    assert(0 <= i && i < m_iVQuantity);
    return m_akVertex[i];
}
//----------------------------------------------------------------------------
inline 
int Polyhedron3::GetTQuantity () const
{
    return m_iTQuantity;
}
//----------------------------------------------------------------------------
inline 
const int* Polyhedron3::GetIndices () const
{
    return m_aiIndex;
}
//----------------------------------------------------------------------------
inline 
const int* Polyhedron3::GetTriangle (int i) const
{
    assert(0 <= i && i < m_iTQuantity);
    return &m_aiIndex[3*i];
}
//----------------------------------------------------------------------------
inline 
void Polyhedron3::SetVertex (int i, const Vector3& rkV)
{
    assert(0 <= i && i < m_iVQuantity);
    m_akVertex[i] = rkV;
}
//----------------------------------------------------------------------------
inline 
Vector3* Polyhedron3::GetVertices ()
{
    return m_akVertex;
}
//----------------------------------------------------------------------------
inline 
Vector3 Polyhedron3::ComputeVertexAverage () const
{
    Vector3 kAverage = m_akVertex[0];
    for (int i = 1; i < m_iVQuantity; i++)
    {
        kAverage += m_akVertex[i];
    }

    kAverage /= (float)m_iVQuantity;
    return kAverage;
}
//----------------------------------------------------------------------------
inline 
float Polyhedron3::ComputeSurfaceArea () const
{
    float fSurfaceArea = (float)0.0;

    const int* piIndex = m_aiIndex;
    for (int i = 0; i < m_iTQuantity; i++)
    {
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;
        Vector3 kEdge0 = m_akVertex[iV1] - m_akVertex[iV0];
        Vector3 kEdge1 = m_akVertex[iV2] - m_akVertex[iV0];
        Vector3 kCross = kEdge0.Cross(kEdge1);
        fSurfaceArea += kCross.Length();
    }

    fSurfaceArea *= (float)0.5;
    return fSurfaceArea;
}
//----------------------------------------------------------------------------
inline 
float Polyhedron3::ComputeVolume () const
{
    float fVolume = (float)0.0;

    const int* piIndex = m_aiIndex;
    for (int i = 0; i < m_iTQuantity; i++)
    {
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;
        fVolume +=
            m_akVertex[iV0].Dot(m_akVertex[iV1].Cross(m_akVertex[iV2]));
    }

    fVolume /= (float)6.0;
    return fVolume;
}
//----------------------------------------------------------------------------

