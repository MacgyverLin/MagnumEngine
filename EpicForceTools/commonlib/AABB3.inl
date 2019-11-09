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
AABB3::AABB3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline AABB3::AABB3 (float fXMin, float fXMax, float fYMin, float fYMax, float fZMin, float fZMax)
{
    Min[0] = fXMin;
    Min[1] = fYMin;
    Min[2] = fZMin;

    Max[0] = fXMax;
    Max[1] = fYMax;
    Max[2] = fZMax;
}
//----------------------------------------------------------------------------
inline bool AABB3::HasXOverlap (const AABB3& rkBox) const
{
    return Max[0] >= rkBox.Min[0] && Min[0] <= rkBox.Max[0];
}
//----------------------------------------------------------------------------
inline bool AABB3::HasYOverlap (const AABB3& rkBox) const
{
    return Max[1] >= rkBox.Min[1] && Min[1] <= rkBox.Max[1];
}
//----------------------------------------------------------------------------
inline bool AABB3::HasZOverlap (const AABB3& rkBox) const
{
    return Max[2] >= rkBox.Min[2] && Min[2] <= rkBox.Max[2];
}
//----------------------------------------------------------------------------
inline bool AABB3::TestIntersection (const AABB3& rkBox) const
{
    for (int i = 0; i < 3; i++)
    {
        if (Max[i] < rkBox.Min[i] || Min[i] > rkBox.Max[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
inline bool AABB3::FindIntersection (const AABB3& rkBox, AABB3& rkIntr) const
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (Max[i] < rkBox.Min[i] || Min[i] > rkBox.Max[i])
        {
            return false;
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (Max[i] <= rkBox.Max[i])
        {
            rkIntr.Max[i] = Max[i];
        }
        else
        {
            rkIntr.Max[i] = rkBox.Max[i];
        }

        if (Min[i] <= rkBox.Min[i])
        {
            rkIntr.Min[i] = rkBox.Min[i];
        }
        else
        {
            rkIntr.Min[i] = Min[i];
        }
    }
    return true;
}
//----------------------------------------------------------------------------

