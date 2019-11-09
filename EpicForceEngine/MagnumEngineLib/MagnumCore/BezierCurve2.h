///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BezierCurve2_h_
#define _BezierCurve2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "SingleCurve2.h"

namespace Magnum
{

class BezierCurve2 : public SingleCurve2
{
public:
    // Construction and destruction.  BezierCurve2 accepts responsibility for
    // deleting the input array.
    BezierCurve2 (int iDegree, Vector2* akCtrlPoint);
    virtual ~BezierCurve2 ();

    int GetDegree () const;
    const Vector2* GetControlPoints () const;

    virtual Vector2 GetPosition (float fTime) const;
    virtual Vector2 GetFirstDerivative (float fTime) const;
    virtual Vector2 GetSecondDerivative (float fTime) const;
    virtual Vector2 GetThirdDerivative (float fTime) const;

    virtual float GetVariation (float fT0, float fT1,
        const Vector2* pkP0 = 0, const Vector2* pkP1 = 0) const;

protected:
    int m_iDegree;
    int m_iNumCtrlPoints;
    Vector2* m_akCtrlPoint;
    Vector2* m_akDer1CtrlPoint;
    Vector2* m_akDer2CtrlPoint;
    Vector2* m_akDer3CtrlPoint;
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

