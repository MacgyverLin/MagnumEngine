///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _IVector2_h_
#define _IVector2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class IVector2
{
public:
    // construction
    IVector2 ();  // uninitialized
    IVector2 (int fX, int fY);
    IVector2 (const int* afTuple);
    IVector2 (const IVector2& rkV);

	void Set(int fX, int fY);

    // coordinate access
    operator const int* () const;
    operator int* ();
    int operator[] (int i) const;
    int& operator[] (int i);
    int X () const;
    int& X ();
    int Y () const;
    int& Y ();

    // assignment
    IVector2& operator= (const IVector2& rkV);

    // comparison
    bool operator== (const IVector2& rkV) const;
    bool operator!= (const IVector2& rkV) const;
    bool operator<  (const IVector2& rkV) const;
    bool operator<= (const IVector2& rkV) const;
    bool operator>  (const IVector2& rkV) const;
    bool operator>= (const IVector2& rkV) const;

    // arithmetic operations
    IVector2 operator+ (const IVector2& rkV) const;
    IVector2 operator- (const IVector2& rkV) const;
    IVector2 operator* (int fScalar) const;
    IVector2 operator/ (int fScalar) const;
    IVector2 operator- () const;

    // arithmetic updates
    IVector2& operator+= (const IVector2& rkV);
    IVector2& operator-= (const IVector2& rkV);
    IVector2& operator*= (int fScalar);
    IVector2& operator/= (int fScalar);

    // special vectors
    static const IVector2 ZERO;    // (0,0)
    static const IVector2 UNIT_X;  // (1,0)
    static const IVector2 UNIT_Y;  // (0,1)
    static const IVector2 ONE;     // (1,1)
    static const IVector2 NULL_;    // (NAN,NAN)

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const IVector2& rkV) const;

    int m_afTuple[2];
};

#include "IVector2.inl"

};

#endif
