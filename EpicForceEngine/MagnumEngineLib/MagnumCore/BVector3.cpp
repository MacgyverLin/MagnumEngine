///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BVector3.h"
using namespace Magnum;

void BVector3::Set(bool fX, bool fY, bool fZ)
{
	m_afTuple[0] = fX;
	m_afTuple[1] = fY;
	m_afTuple[2] = fZ;
}

BVector3 &BVector3::operator= (const BVector3& rkV)
{
	m_afTuple[0] = rkV.m_afTuple[0];
	m_afTuple[1] = rkV.m_afTuple[1];
	m_afTuple[2] = rkV.m_afTuple[2];

	return *this;
}