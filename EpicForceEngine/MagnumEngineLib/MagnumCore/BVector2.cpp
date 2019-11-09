///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BVector2.h"
using namespace Magnum;

void BVector2::Set(bool fX, bool fY)
{
	m_afTuple[0] = fX;
	m_afTuple[1] = fY;
}

BVector2 &BVector2::operator= (const BVector2& rkV)
{
	m_afTuple[0] = rkV.m_afTuple[0];
	m_afTuple[1] = rkV.m_afTuple[1];

	return *this;
}