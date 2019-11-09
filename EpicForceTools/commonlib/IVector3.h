///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _IVector3_h_
#define _IVector3_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class IVector3
{
public:
    // construction
    IVector3 ();  // uninitialized
    IVector3 (int fX, int fY, int fZ);
    IVector3 (const int* afTuple);
    IVector3 (const IVector3& rkV);

	void Set (int fX, int fY, int fZ);

    // coordinate access
    operator const int* () const;
    operator int* ();
    int operator[] (int i) const;
    int& operator[] (int i);
    int X () const;
    int& X ();
    int Y () const;
    int& Y ();
    int Z () const;
    int& Z ();

    // assignment
    IVector3& operator= (const IVector3& rkV);

    // comparison
    bool operator== (const IVector3& rkV) const;
    bool operator!= (const IVector3& rkV) const;
    bool operator<  (const IVector3& rkV) const;
    bool operator<= (const IVector3& rkV) const;
    bool operator>  (const IVector3& rkV) const;
    bool operator>= (const IVector3& rkV) const;

    // arithmetic operations
    IVector3 operator+ (const IVector3& rkV) const;
    IVector3 operator- (const IVector3& rkV) const;
    IVector3 operator* (int fScalar) const;
    IVector3 operator/ (int fScalar) const;
    IVector3 operator- () const;

    // arithmetic updates
    IVector3& operator+= (const IVector3& rkV);
    IVector3& operator-= (const IVector3& rkV);
    IVector3& operator*= (int fScalar);
    IVector3& operator/= (int fScalar);

    // special vectors
    static const IVector3 ZERO;    // (0,0,0)
    static const IVector3 UNIT_X;  // (1,0,0)
    static const IVector3 UNIT_Y;  // (0,1,0)
    static const IVector3 UNIT_Z;  // (0,0,1)
    static const IVector3 ONE;     // (1,1,1)

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const IVector3& rkV) const;

    int m_afTuple[3];
};

#include "IVector3.inl"

};

#endif
