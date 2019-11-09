///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Rectangle2_h_
#define _Rectangle2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Rectangle2
{
public:
    // construction
    Rectangle2();  // uninitialized
    Rectangle2(float fX, float fY, float fWidth, float fHeight);
    Rectangle2(const float* afTuple);
    Rectangle2(const Rectangle2& rkV);

	void Set(float fX, float fY, float fWidth, float fHeight);

    // coordinate access
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float &operator[] (int i);
    float X () const;
    float &X ();
    float Y () const;
    float &Y ();
    float Width () const;
    float &Width ();
    float Height () const;
    float &Height ();

    // assignment
    Rectangle2 &operator= (const Rectangle2 &rkV);

    // comparison
    bool operator== (const Rectangle2 &rkV) const;
    bool operator!= (const Rectangle2 &rkV) const;
    bool operator<  (const Rectangle2 &rkV) const;
    bool operator<= (const Rectangle2 &rkV) const;
    bool operator>  (const Rectangle2 &rkV) const;
    bool operator>= (const Rectangle2 &rkV) const;

    // arithmetic operations
    Rectangle2 operator+ (const Rectangle2& rkV) const;
    Rectangle2 operator- (const Rectangle2& rkV) const;
    Rectangle2 operator* (float fScalar) const;
    Rectangle2 operator/ (float fScalar) const;
    Rectangle2 operator- () const;

    // arithmetic updates
    Rectangle2& operator+= (const Rectangle2& rkV);
    Rectangle2& operator-= (const Rectangle2& rkV);
    Rectangle2& operator*= (float fScalar);
    Rectangle2& operator/= (float fScalar);

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // support for comparisons
    int CompareArrays (const Rectangle2& rkV) const;

    float m_afTuple[4];
};

// arithmetic operations
Rectangle2 operator* (float fScalar, const Rectangle2& rkV);

#include "Rectangle2.inl"

};

#endif
