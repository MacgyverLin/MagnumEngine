///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "IO.h"
using namespace Magnum;

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