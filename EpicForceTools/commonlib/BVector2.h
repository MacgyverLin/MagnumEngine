///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _BVector2_h_
#define _BVector2_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class BVector2
{
public:
    // construction
    BVector2() // uninitialized
	{
	}

	void Set(bool fX, bool fY);

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
