///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BVector4.h"
using namespace Magnum;

void BVector4::Set(bool fX, bool fY, bool fZ, bool fW)
{
	m_afTuple[0] = fX;
	m_afTuple[1] = fY;
	m_afTuple[2] = fZ;
	m_afTuple[3] = fW;
}

BVector4 &BVector4::operator= (const BVector4& rkV)
{
	m_afTuple[0] = rkV.m_afTuple[0];
	m_afTuple[1] = rkV.m_afTuple[1];
	m_afTuple[2] = rkV.m_afTuple[2];
	m_afTuple[3] = rkV.m_afTuple[3];

	return *this;
}