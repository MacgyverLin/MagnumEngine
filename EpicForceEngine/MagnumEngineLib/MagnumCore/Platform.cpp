///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Platform.h"
using namespace Magnum;

const Platform Platform::EDITOR		= 0;
const Platform Platform::PC			= 1;
const Platform Platform::IMAC		= 2;
const Platform Platform::IPHONE		= 3;
const Platform Platform::IPAD		= 4;

bool Platform::operator == (const Platform &p_) const
{
	return id == p_.id;
}

void Platform::read(InputStream &is)
{
	is >> id;
}

void Platform::write(OutputStream &os) const
{
	os << id;
}