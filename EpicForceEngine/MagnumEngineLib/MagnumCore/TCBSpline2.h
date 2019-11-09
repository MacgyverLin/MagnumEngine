///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TCBSpline2_h_
#define _TCBSpline2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"
#include "MultipleCurve2.h"

namespace Magnum
{

class TCBSpline2 : public MultipleCurve2
{
public:
    // Construction and destruction.  TCBSpline2 accepts responsibility for
    // deleting the input arrays.
    TCBSpline2 (int iSegments, float* afTime, Vector2* akPoint,
        float* afTension, float* afContinuity, float* afBias);

    virtual ~TCBSpline2 ();

    const Vector2* GetPoints () const;
    const float* GetTensions () const;
    const float* GetContinuities () const;
    const float* GetBiases () const;

    virtual Vector2 GetPosition (float fTime) const;
    virtual Vector2 GetFirstDerivative (float fTime) const;
    virtual Vector2 GetSecondDerivative (float fTime) const;
    virtual Vector2 GetThirdDerivative (float fTime) const;

protected:
    using MultipleCurve2::m_iSegments;
    using MultipleCurve2::m_afTime;
    using MultipleCurve2::GetSpeedWithData;

    void ComputePoly (int i0, int i1, int i2, int i3);

    virtual float GetSpeedKey (int iKey, float fTime) const;
    virtual float GetLengthKey (int iKey, float fT0, float fT1) const;
    virtual float GetVariationKey (int iKey, float fT0, float fT1,
        const Vector2& rkA, const Vector2& rkB) const;

    Vector2* m_akPoint;
    float* m_afTension;
    float* m_afContinuity;
    float* m_afBias;
    Vector2* m_akA;
    Vector2* m_akB;
    Vector2* m_akC;
    Vector2* m_akD;

    class ThisPlusKey
    {
    public:
        ThisPlusKey (const TCBSpline2* pkThis, int iKey)
            :
            This(pkThis),
            Key(iKey)
        {
        }

        const TCBSpline2* This;
        int Key;
    };
};

}

#endif

