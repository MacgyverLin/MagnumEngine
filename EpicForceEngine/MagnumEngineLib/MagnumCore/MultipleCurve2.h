///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MultipleCurve2_h_
#define _MultipleCurve2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Curve2.h"

namespace Magnum
{

class MultipleCurve2 : public Curve2
{
public:
    // Construction and destruction for abstract base class.  MultipleCurve2
    // accepts responsibility for deleting the input array.
    MultipleCurve2 (int iSegments, float* afTime);
    virtual ~MultipleCurve2 ();

    // member access
    int GetSegments () const;
    const float* GetTimes () const;

    // length-from-time and time-from-length
    virtual float GetLength (float fT0, float fT1) const;
    virtual float GetTime (float fLength, int iIterations = 32,
        float fTolerance = (float)1e-06) const;

    // support for subdivision
    virtual float GetVariation (float fT0, float fT1,
        const Vector2* pkP0 = 0, const Vector2* pkP1 = 0) const;

protected:
    using Curve2::m_fTMin;
    using Curve2::m_fTMax;

    int m_iSegments;
    float* m_afTime;

    // These quantities are allocated by GetLength when they are needed the
    // first time.  The allocations occur in InitializeLength (called by
    // GetLength), so this member function must be 'const'. In order to
    // allocate the arrays in a 'const' function, they must be declared as
    // 'mutable'.
    mutable float* m_afLength;
    mutable float* m_afAccumLength;

    void GetKeyInfo (float fTime, int& riKey, float& rfDt) const;

    void InitializeLength () const;
    virtual float GetSpeedKey (int iKey, float fTime) const = 0;
    virtual float GetLengthKey (int iKey, float fT0, float fT1) const = 0;
    virtual float GetVariationKey (int iKey, float fT0, float fT1,
        const Vector2& rkA, const Vector2& rkB) const = 0;

    static float GetSpeedWithData (float fTime, void* pvData);
};

}

#endif

