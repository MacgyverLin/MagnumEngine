///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TCBSpline3_h_
#define _TCBSpline3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "MultipleCurve3.h"

namespace Magnum
{

class TCBSpline3 : public MultipleCurve3
{
public:
    // Construction and destruction.  TCBSpline3 accepts responsibility for
    // deleting the input arrays.
    TCBSpline3 (int iSegments, float* afTime, Vector3* akPoint,
        float* afTension, float* afContinuity, float* afBias);

    virtual ~TCBSpline3 ();

    const Vector3* GetPoints () const;
    const float* GetTensions () const;
    const float* GetContinuities () const;
    const float* GetBiases () const;

    virtual Vector3 GetPosition (float fTime) const;
    virtual Vector3 GetFirstDerivative (float fTime) const;
    virtual Vector3 GetSecondDerivative (float fTime) const;
    virtual Vector3 GetThirdDerivative (float fTime) const;

protected:
    using MultipleCurve3::m_iSegments;
    using MultipleCurve3::m_afTime;
    using MultipleCurve3::GetSpeedWithData;

    void ComputePoly (int i0, int i1, int i2, int i3);

    virtual float GetSpeedKey (int iKey, float fTime) const;
    virtual float GetLengthKey (int iKey, float fT0, float fT1) const;
    virtual float GetVariationKey (int iKey, float fT0, float fT1,
        const Vector3& rkA, const Vector3& rkB) const;

    Vector3* m_akPoint;
    float* m_afTension;
    float* m_afContinuity;
    float* m_afBias;
    Vector3* m_akA;
    Vector3* m_akB;
    Vector3* m_akC;
    Vector3* m_akD;

    class ThisPlusKey
    {
    public:
        ThisPlusKey (const TCBSpline3* pkThis, int iKey)
            :
            This(pkThis),
            Key(iKey)
        {
        }

        const TCBSpline3* This;
        int Key;
    };
};

}

#endif

