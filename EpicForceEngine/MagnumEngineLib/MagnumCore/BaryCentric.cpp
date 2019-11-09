///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BaryCentric.h"
using namespace Magnum;

BaryCentric::BaryCentric(const Vector3 &a_, const Vector3 &b_, const Vector3 &c_)
: a(a_)
, b(b_)
, c(c_)
{
}

bool BaryCentric::isInside(const Vector3 &p) const
{
	Vector2 rval = getBaryCentricPoint(p);

	return (rval.X() >= 0) && (rval.Y() >= 0) && (rval.X() + rval.Y() < 1.0f);
}

Vector2 BaryCentric::getBaryCentricPoint(const Vector3 &p) const
{
	Vector2 rval;

	Vector3 v0(c - a);
	Vector3 v1(b - a);
	Vector3 v2(p - a);

	float dot00 = v0.Dot(v0);
	float dot01 = v0.Dot(v1);
	float dot02 = v0.Dot(v2);
	float dot11 = v1.Dot(v1);
	float dot12 = v1.Dot(v2);

	float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
	rval[0] = (dot11 * dot02 - dot01 * dot12) * invDenom;
	rval[1] = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return rval;
}

Vector3 BaryCentric::getPoint(const Vector2 &uv) const
{
	return a + uv.X() * (c - a) + uv.Y() * (b - a) ;
}