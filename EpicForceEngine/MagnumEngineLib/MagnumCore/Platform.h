///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Platform_h_
#define _Platform_h_

#include "Stage.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Platform
{
public:
	Platform(int id_ = 0)
	{
		id = id_;
	}

	bool operator == (const Platform &p_) const;
	void read(InputStream &is);
	void write(OutputStream &os) const;

	const static Platform EDITOR;
	const static Platform PC;
	const static Platform IMAC;
	const static Platform IPHONE;
	const static Platform IPAD;
private:
	int id;
};

};

#endif
