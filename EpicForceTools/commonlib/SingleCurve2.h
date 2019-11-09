// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _SingleCurve2_h_
#define _SingleCurve2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Curve2.h"

namespace EpicForce
{

class SingleCurve2 : public Curve2
{
public:
    // abstract base class
    SingleCurve2 (float fTMin, float fTMax);

    // length-from-time and time-from-length
    virtual float GetLength (float fT0, float fT1) const;
    virtual float GetTime (float fLength, int iIterations = 32,
        float fTolerance = (float)1e-06) const;

protected:
    using Curve2::m_fTMin;
    using Curve2::m_fTMax;
    using Curve2::GetTotalLength;

    static float GetSpeedWithData (float fTime, void* pvData);
};

}

#endif

