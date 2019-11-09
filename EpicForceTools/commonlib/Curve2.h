///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Curve2_h_
#define _Curve2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector2.h"

namespace EpicForce
{

class Curve2
{
public:
    // abstract base class
    Curve2 (float fTMin, float fTMax);
    virtual ~Curve2 ();

    // Interval on which curve parameter is defined.  If you are interested
    // in only a subinterval of the actual domain of the curve, you may set
    // that subinterval with SetTimeInterval.  This function requires that
    // fTMin < fTMax.
    float GetMinTime () const;
    float GetMaxTime () const;
    void SetTimeInterval (float fTMin, float fTMax);

    // position and derivatives
    virtual Vector2 GetPosition (float fTime) const = 0;
    virtual Vector2 GetFirstDerivative (float fTime) const = 0;
    virtual Vector2 GetSecondDerivative (float fTime) const = 0;
    virtual Vector2 GetThirdDerivative (float fTime) const = 0;

    // differential geometric quantities
    float GetSpeed (float fTime) const;
    virtual float GetLength (float fT0, float fT1) const = 0;
    float GetTotalLength () const;
    Vector2 GetTangent (float fTime) const;
    Vector2 GetNormal (float fTime) const;
    void GetFrame (float fTime, Vector2& rkPosition,
        Vector2& rkTangent, Vector2& rkNormal) const;
    float GetCurvature (float fTime) const;

    // inverse mapping of s = Length(t) given by t = Length^{-1}(s)
    virtual float GetTime (float fLength, int iIterations = 32,
        float fTolerance = (float)1e-06) const = 0;

    // subdivision
    void SubdivideByTime (int iNumPoints, Vector2*& rakPoint) const;
    void SubdivideByLength (int iNumPoints, Vector2*& rakPoint) const;

    // Subdivision by variation. The pointers pkP0 and pkP1 correspond to the
    // curve points at fT0 and fT1.  If the pointer values are not null, the
    // assumption is that the caller has passed in the curve points.
    // Otherwise, the function computes the curve points.
    virtual float GetVariation (float fT0, float fT1,
        const Vector2* pkP0 = 0, const Vector2* pkP1 = 0)
        const = 0;
    void SubdivideByVariation (float fMinVariation, int iMaxLevel,
        int& riNumPoints, Vector2*& rakPoint) const;

protected:
    // curve parameter is t where tmin <= t <= tmax
    float m_fTMin, m_fTMax;

    // subdivision
    class PointList
    {
    public:
        PointList (const Vector2& rkPoint, PointList* pkNext)
        {
            m_kPoint = rkPoint;
            m_kNext = pkNext;
        }

        Vector2 m_kPoint;
        PointList* m_kNext;
    };

    void SubdivideByVariation (float fT0, const Vector2& rkP0, float fT1,
        const Vector2& rkP1, float kMinVariation, int iLevel,
        int& riNumPoints, PointList*& rpkList) const;
};

}

#endif

