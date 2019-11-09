///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Shape3.h"
using namespace Magnum;

Shape3::Shape3(Shape3::Type type_)
: type(type_)
, boundingBox(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5)
, volume(1)
, handle(0)
{
}

Shape3::~Shape3()
{
}

Shape3::Type Shape3::getType() const
{
	return type;
}

const Shape3 *Shape3::getChild(int i) const
{
	return 0;
}

Shape3 *Shape3::getChild(int i)
{
	return 0;
}

int Shape3::getNumChildren() const
{
	return 0;
}

const AABB3 &Shape3::getBoundingBox() const
{
	return boundingBox;
}

float Shape3::getVolume() const
{
	return volume;
}

void *Shape3::getHandle() const
{
	return handle;
}