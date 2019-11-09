///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _IVector4_h_
#define _IVector4_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class IVector4
{
public:
    // construction
    IVector4 ();  // uninitialized
    IVector4 (int fX, int fY, int fZ, int fW);
    IVector4 (const int* afTuple);
    IVector4 (const IVector4& rkV);

	void Set (int fX, int fY, int fZ, int fW);

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
    int W () const;
    int& W ();

    // assignment
    IVector4& operator= (const IVector4& rkV);

    // comparison
    bool operator== (const IVector4& rkV) const;
    bool operator!= (const IVector4& rkV) const;
    bool operator<  (const IVector4& rkV) const;
    bool operator<= (const IVector4& rkV) const;
    bool operator>  (const IVector4& rkV) const;
    bool operator>= (const IVector4& rkV) const;

    // arithmetic operations
    IVector4 operator+ (const IVector4& rkV) const;
    IVector4 operator- (const IVector4& rkV) const;
    IVector4 operator* (int fScalar) const;
    IVector4 operator/ (int fScalar) const;
    IVector4 operator- () const;

    // arithmetic updates
    IVector4& operator+= (const IVector4& rkV);
    IVector4& operator-= (const IVector4& rkV);
    IVector4& operator*= (int fScalar);
    IVector4& operator/= (int fScalar);

    // special vectors
    static const IVector4 ZERO;    // (0,0,0,0)
    static const IVector4 UNIT_X;  // (1,0,0,0)
    static const IVector4 UNIT_Y;  // (0,1,0,0)
    static const IVector4 UNIT_Z;  // (0,0,1,0)
    static const IVector4 UNIT_W;  // (0,0,0,1)
    static const IVector4 ONE;     // (1,1,1,1)
	
	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const IVector4& rkV) const;

    int m_afTuple[4];
};

// arithmetic operations
IVector4 operator* (int fScalar, const IVector4& rkV);

#include "IVector4.inl"

};

#endif
