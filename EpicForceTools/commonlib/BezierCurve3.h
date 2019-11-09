///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _BezierCurve3_h_
#define _BezierCurve3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "SingleCurve3.h"

namespace EpicForce
{

class BezierCurve3 : public SingleCurve3
{
public:
    // Construction and destruction.  BezierCurve3 accepts responsibility for
    // deleting the input arrays.
    BezierCurve3 (int iDegree, Vector3* akCtrlPoint);
    virtual ~BezierCurve3 ();

    int GetDegree () const;
    const Vector3* GetControlPoints () const;

    virtual Vector3 GetPosition (float fTime) const;
    virtual Vector3 GetFirstDerivative (float fTime) const;
    virtual Vector3 GetSecondDerivative (float fTime) const;
    virtual Vector3 GetThirdDerivative (float fTime) const;

    virtual float GetVariation (float fT0, float fT1,
        const Vector3* pkP0 = 0, const Vector3* pkP1 = 0) const;

protected:
    int m_iDegree;
    int m_iNumCtrlPoints;
    Vector3* m_akCtrlPoint;
    Vector3* m_akDer1CtrlPoint;
    Vector3* m_akDer2CtrlPoint;
    Vector3* m_akDer3CtrlPoint;
    float** m_aafChoose;

    // variation support
    int m_iTwoDegree;
    int m_iTwoDegreePlusOne;
    float* m_afSigma;
    float* m_afRecip;
    float* m_afPowT0;
    float* m_afPowOmT0;
    float* m_afPowT1;
    float* m_afPowOmT1;
};

}

#endif

