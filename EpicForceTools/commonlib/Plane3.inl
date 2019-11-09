///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Plane3::Plane3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline Plane3::Plane3 (const Plane3& rkPlane)
    :
    Normal(rkPlane.Normal)
{
    Constant = rkPlane.Constant;
}
//----------------------------------------------------------------------------
inline Plane3::Plane3 (const Vector3& rkNormal, float fConstant)
    :
    Normal(rkNormal)
{
    Constant = fConstant;
}
//----------------------------------------------------------------------------
inline Plane3::Plane3 (const Vector3& rkNormal, const Vector3& rkP)
    :
    Normal(rkNormal)
{
    Constant = rkNormal.Dot(rkP);
}
//----------------------------------------------------------------------------
inline Plane3::Plane3 (const Vector3& rkP0, const Vector3& rkP1,
    const Vector3& rkP2)
{
    Vector3 kEdge1 = rkP1 - rkP0;
    Vector3 kEdge2 = rkP2 - rkP0;
    Normal = kEdge1.UnitCross(kEdge2);
    Constant = Normal.Dot(rkP0);
}
//----------------------------------------------------------------------------
inline Plane3& Plane3::operator= (const Plane3& rkPlane)
{
    Normal = rkPlane.Normal;
    Constant = rkPlane.Constant;
    return *this;
}
//----------------------------------------------------------------------------
inline float Plane3::DistanceTo (const Vector3& rkP) const
{
    return Normal.Dot(rkP) - Constant;
}

//----------------------------------------------------------------------------
inline bool Plane3::isCoplanar(const Plane3& rkPlane) const
{
	return fabs(Normal[0]-rkPlane.Normal[0])<0.01f &&
		   fabs(Normal[1]-rkPlane.Normal[1])<0.01f &&
		   fabs(Normal[2]-rkPlane.Normal[2])<0.01f &&
		   fabs(Constant -rkPlane.Constant )<0.01f;
}

//----------------------------------------------------------------------------
inline void Plane3::read(InputStream &is)
{
	is >> Normal >> Constant;
}

//----------------------------------------------------------------------------
inline void Plane3::write(OutputStream &os) const
{
	os << Normal << Constant;
}

//----------------------------------------------------------------------------
inline int Plane3::WhichSide (const Vector3& rkQ) const
{
    float fDistance = DistanceTo(rkQ);

    if (fDistance < (float)0.0)
    {
        return -1;
    }

    if (fDistance > (float)0.0)
    {
        return +1;
    }

    return 0;
}
