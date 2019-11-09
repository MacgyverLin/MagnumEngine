///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoPhysicsDiffuseMapCubeEntity.h"
using namespace Magnum;

MacDemoPhysicsDiffuseMapCubeEntity::MacDemoPhysicsDiffuseMapCubeEntity()
: diffuseMapCubeRenderer(*this)
, diffuseMapCube(*this)
, boxCollider(*this)
{
	diffuseMapCubeRenderer.add(diffuseMapCube);
}

MacDemoPhysicsDiffuseMapCubeEntity::~MacDemoPhysicsDiffuseMapCubeEntity()
{
	diffuseMapCubeRenderer.remove(diffuseMapCube);
}

bool MacDemoPhysicsDiffuseMapCubeEntity::onConstruct()
{
	return true;
}

void MacDemoPhysicsDiffuseMapCubeEntity::onStart()
{
}

void MacDemoPhysicsDiffuseMapCubeEntity::onPause()
{
}

void MacDemoPhysicsDiffuseMapCubeEntity::onResume()
{
}

void MacDemoPhysicsDiffuseMapCubeEntity::onUpdate(float dt)
{
}

void MacDemoPhysicsDiffuseMapCubeEntity::onStop()
{
}

void MacDemoPhysicsDiffuseMapCubeEntity::onDestruct()
{
}