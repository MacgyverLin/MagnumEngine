///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Platform.h"
using namespace EpicForce;

const Platform Platform::PC			= 0;
const Platform Platform::IOS		= 1;
const Platform Platform::ANDROID	= 2;
const Platform Platform::PSVITA		= 3;
const Platform Platform::WIIU		= 4;

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