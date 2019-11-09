///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "CapsuleBound.h"
using namespace Magnum;

CapsuleBound::CapsuleBound(Component::Owner &owner_)
: Selection3::Bound(owner_)
{
	setRadius(1.0f);
	setAxis(Vector3::UNIT_Y);
}

CapsuleBound::~CapsuleBound()
{
}

bool CapsuleBound::rayCast(const Vector3 &from, const Vector3 &dir)
{
	return true;
}

bool CapsuleBound::sphereCast(const Vector3 &from, float radius, const Vector3 &dir)
{
	return true;
}