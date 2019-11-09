///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BVector4_h_
#define _BVector4_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class BVector4
{
public:
    // construction
    BVector4() // uninitialized
	{
	}

	void Set(bool fX, bool fY, bool fZ, bool fW);

	BVector4& operator= (const BVector4& rkV);

    // coordinate access
    operator const bool* () const;
    operator bool* ();
    bool operator[] (int i) const;
    bool& operator[] (int i);
    bool X () const;
    bool& X ();
    bool Y () const;
    bool& Y ();
    bool Z () const;
    bool& Z ();
    bool W () const;
    bool& W ();
	
	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    bool m_afTuple[4];
};

#include "BVector4.inl"

};

#endif
