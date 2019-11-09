///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SingleCurve2_h_
#define _SingleCurve2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Curve2.h"

namespace Magnum
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
