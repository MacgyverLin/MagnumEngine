///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoPhysicsDiffuseMapSpecularMapCubeEntity.h"
using namespace Magnum;

MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::MacDemoPhysicsDiffuseMapSpecularMapCubeEntity()
: diffuseMapSpecularMapCubeRenderer(*this)
, diffuseMapSpecularMapCube(*this)
, boxCollider(*this)
{
	diffuseMapSpecularMapCubeRenderer.add(diffuseMapSpecularMapCube);
}

MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::~MacDemoPhysicsDiffuseMapSpecularMapCubeEntity()
{
	diffuseMapSpecularMapCubeRenderer.remove(diffuseMapSpecularMapCube);
}

bool MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onConstruct()
{
	return true;
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onStart()
{
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onStop()
{
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onUpdate(float dt)
{
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onPause()
{
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onResume()
{
}

void MacDemoPhysicsDiffuseMapSpecularMapCubeEntity::onDestruct()
{
}