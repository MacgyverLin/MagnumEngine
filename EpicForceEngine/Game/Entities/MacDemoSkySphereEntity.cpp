///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoSkySphereEntity.h"
using namespace Magnum;

MacDemoSkySphereEntity::MacDemoSkySphereEntity()
: skySphereRenderer(*this)
, skySphere(*this)
{
	skySphereRenderer.add(skySphere);
}

MacDemoSkySphereEntity::~MacDemoSkySphereEntity()
{
	skySphereRenderer.remove(skySphere);
}

bool MacDemoSkySphereEntity::onConstruct()
{
	return true;
}

void MacDemoSkySphereEntity::onStart()
{
}

void MacDemoSkySphereEntity::onPause()
{
}

void MacDemoSkySphereEntity::onResume()
{
}

void MacDemoSkySphereEntity::onUpdate(float dt)
{
}

void MacDemoSkySphereEntity::onStop()
{
}

void MacDemoSkySphereEntity::onDestruct()
{
}
