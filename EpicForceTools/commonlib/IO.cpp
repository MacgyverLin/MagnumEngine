///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "IO.h"
using namespace EpicForce;

IO::IO(const char *path_)
: path(path_)
, accessMode(IO::READ)
{
}

IO::~IO()
{
}

bool IO::open(AccessMode accessMode)
{
	assert(accessMode);

	this->accessMode	= accessMode;
	this->asyncMode		= false;

	return true;
}

bool IO::openForAsync(AccessMode accessMode)
{
	assert(accessMode);

	this->accessMode	= accessMode;
	this->asyncMode		= true;

	return true;
}

bool IO::isReadEnabled() const
{
	return ((accessMode & IO::READ)!=0);
}

bool IO::isWriteEnabled() const
{
	return ((accessMode & IO::WRITE)!=0);
}

const char *IO::getPath() const
{
	return path.text();
}