///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BVector2_h_
#define _BVector2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class BVector2
{
public:
    // construction
    BVector2() // uninitialized
	{
	}

	void Set(bool fX, bool fY);

    // assignment
    BVector2& operator= (const BVector2& rkV);

    // coordinate access
    operator const bool* () const;
    operator bool* ();
    bool operator[] (int i) const;
    bool& operator[] (int i);
    bool X () const;
    bool& X ();
    bool Y () const;
    bool& Y ();
	
	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    bool m_afTuple[2];
};

#include "BVector2.inl"

};

#endif
