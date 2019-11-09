///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _BVector4_h_
#define _BVector4_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class BVector4
{
public:
    // construction
    BVector4() // uninitialized
	{
	}

	void Set(bool fX, bool fY, bool fZ, bool fW);

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
