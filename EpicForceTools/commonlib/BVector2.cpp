///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "BVector2.h"
using namespace EpicForce;

void BVector2::Set(bool fX, bool fY)
{
	m_afTuple[0] = fX;
	m_afTuple[1] = fY;
}