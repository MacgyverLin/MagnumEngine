///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Arc2::Arc2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline Arc2::Arc2 (const Vector2& rkCenter, float fRadius,
    const Vector2& rkEnd0, const Vector2& rkEnd1)
    :
    Circle2(rkCenter,fRadius),
    End0(rkEnd0),
    End1(rkEnd1)
{
}
//----------------------------------------------------------------------------
inline bool Arc2::Contains (const Vector2& rkP) const
{
    // Assert: |P-C| = R where P is the input point, C is the circle center,
    // and R is the circle radius.  For P to be on the arc from A to B, it
    // must be on the side of the plane containing A with normal N = Perp(B-A)
    // where Perp(u,v) = (v,-u).

    Vector2 kPmE0 = rkP - End0;
    Vector2 kE1mE0 = End1 - End0;
    float fDotPerp = kPmE0.DotPerp(kE1mE0);
    return fDotPerp >= (float)0.0;
}
//----------------------------------------------------------------------------
inline float Arc2::GetAngleEnd0 () const
{
    Vector2 kDiff = End0 - Center;
    float fAngle;

    if (kDiff != Vector2::ZERO)
    {
        // This angle is in (-pi,pi].  To have an angle in [0,2*pi), we can
        // just use the current angle if it is in [0,pi], but we must add
        // 2*pi to the current angle if it is in (-pi,0).
        fAngle = Math::ATan2(kDiff.Y(),kDiff.X());
        if (fAngle < (float)0.0)
        {
            fAngle += Math::TWO_PI;
        }
    }
    else
    {
        // diff = (0,0), return an angle of 0 since atan2 is undefined
        fAngle = (float)0.0;
    }

    return fAngle;
}
//----------------------------------------------------------------------------
inline float Arc2::GetAngleEnd1 () const
{
    Vector2 kDiff = End1 - Center;
    float fAngle;

    if (kDiff != Vector2::ZERO)
    {
        // This angle is in (-pi,pi].  To have an angle in [0,2*pi), we can
        // just use the current angle if it is in [0,pi], but we must add
        // 2*pi to the current angle if it is in (-pi,0).
        fAngle = Math::ATan2(kDiff.Y(),kDiff.X());
        if (fAngle < (float)0.0)
        {
            fAngle += Math::TWO_PI;
        }
    }
    else
    {
        // diff = (0,0), return an angle of 0 since atan2 is undefined
        fAngle = (float)0.0;
    }

    return fAngle;
}
//----------------------------------------------------------------------------
inline float Arc2::GetAngle () const
{
    float fAngle = GetAngleEnd1() - GetAngleEnd0();
    if (fAngle < (float)0.0)
    {
        fAngle += Math::TWO_PI;
    }
    return fAngle;
}
//----------------------------------------------------------------------------

