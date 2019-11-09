///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline AABB2::AABB2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
inline AABB2::AABB2 (float fXMin, float fXMax, float fYMin,
    float fYMax)
{
    Min[0] = fXMin;
	Min[1] = fYMin;

    Max[0] = fXMax;
    Max[1] = fYMax;
}
//----------------------------------------------------------------------------
inline bool AABB2::HasXOverlap (const AABB2& rkBox) const
{
    return Max[0] >= rkBox.Min[0] && Min[0] <= rkBox.Max[0];
}
//----------------------------------------------------------------------------
inline bool AABB2::HasYOverlap (const AABB2& rkBox) const
{
    return Max[1] >= rkBox.Min[1] && Min[1] <= rkBox.Max[1];
}
//----------------------------------------------------------------------------
inline bool AABB2::TestIntersection (const AABB2& rkBox)
    const
{
    for (int i = 0; i < 2; i++)
    {
        if (Max[i] < rkBox.Min[i] || Min[i] > rkBox.Max[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
inline bool AABB2::FindIntersection (const AABB2& rkBox,
    AABB2& rkIntr) const
{
    int i;
    for (i = 0; i < 2; i++)
    {
        if (Max[i] < rkBox.Min[i] || Min[i] > rkBox.Max[i])
        {
            return false;
        }
    }

    for (i = 0; i < 2; i++)
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
inline void AABB2::read(InputStream &is)
{
	is >> Min >> Max;
}

inline void AABB2::write(OutputStream &os) const
{
	os << Min << Max;
}