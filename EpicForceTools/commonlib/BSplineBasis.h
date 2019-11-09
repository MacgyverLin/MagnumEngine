///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _BSplineBasis_h_
#define _BSplineBasis_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "EMath.h"

namespace EpicForce
{

class BSplineBasis
{
public:
    BSplineBasis ();

    // Open uniform or periodic uniform.  The knot array is internally
    // generated with equally spaced elements.
    BSplineBasis (int iNumCtrlPoints, int iDegree, bool bOpen);
    void Create (int iNumCtrlPoints, int iDegree, bool bOpen);

    // Open nonuniform.  The knot array must have n-d elements.  The elements
    // must be nondecreasing.  Each element must be in [0,1].  The caller is
    // responsible for deleting afKnot.  An internal copy is made, so to
    // dynamically change knots you must use the SetKnot function.
    BSplineBasis (int iNumCtrlPoints, int iDegree, const float* afKnot);
    void Create (int iNumCtrlPoints, int iDegree, const float* afKnot);

    virtual ~BSplineBasis ();

    int GetNumCtrlPoints () const;
    int GetDegree () const;
    bool IsOpen () const;
    bool IsUniform () const;

    // The knot values can be changed only if the basis function is nonuniform
    // and the input index is valid (0 <= i <= n-d-1).  If these conditions
    // are not satisfied, GetKnot returns MAX_REAL.
    void SetKnot (int i, float fKnot);
    float GetKnot (int i) const;

    // access basis functions and their derivatives
    float GetD0 (int i) const;
    float GetD1 (int i) const;
    float GetD2 (int i) const;
    float GetD3 (int i) const;

    // evaluate basis functions and their derivatives
    void Compute (float fTime, unsigned int uiOrder, int& riMinIndex,
        int& riMaxIndex) const;

protected:
    int Initialize (int iNumCtrlPoints, int iDegree, bool bOpen);
    float** Allocate () const;
    void Deallocate (float** aafArray);

    // Determine knot index i for which knot[i] <= rfTime < knot[i+1].
    int GetKey (float& rfTime) const;

    int m_iNumCtrlPoints;    // n+1
    int m_iDegree;           // d
    float* m_afKnot;          // knot[n+d+2]
    bool m_bOpen, m_bUniform;

    // Storage for the basis functions and their derivatives first three
    // derivatives.  The basis array is always allocated by the constructor
    // calls.  A derivative basis array is allocated on the first call to a
    // derivative member function.
    float** m_aafBD0;             // bd0[d+1][n+d+1]
    mutable float** m_aafBD1;     // bd1[d+1][n+d+1]
    mutable float** m_aafBD2;     // bd2[d+1][n+d+1]
    mutable float** m_aafBD3;     // bd3[d+1][n+d+1]
};

}

#endif

