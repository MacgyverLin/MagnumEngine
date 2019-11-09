///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Platform_h_
#define _Platform_h_

#include "Stage.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
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

	const static Platform PC;
	const static Platform IOS;
	const static Platform ANDROID;
	const static Platform PSVITA;
	const static Platform WIIU;
private:
	int id;
};

};

#endif