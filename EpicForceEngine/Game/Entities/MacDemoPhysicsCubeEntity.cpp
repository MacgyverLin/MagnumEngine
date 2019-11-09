///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoPhysicsCubeEntity.h"
using namespace Magnum;

MacDemoPhysicsCubeEntity::MacDemoPhysicsCubeEntity()
: cubeRenderer(*this)
, cube(*this)
, boxCollider(*this)
{
	cubeRenderer.add(cube);
}

MacDemoPhysicsCubeEntity::~MacDemoPhysicsCubeEntity()
{
	cubeRenderer.remove(cube);
}

bool MacDemoPhysicsCubeEntity::onConstruct()
{
	return true;
}

void MacDemoPhysicsCubeEntity::onStart()
{
}

void MacDemoPhysicsCubeEntity::onPause()
{
}

void MacDemoPhysicsCubeEntity::onResume()
{
}

void MacDemoPhysicsCubeEntity::onUpdate(float dt)
{
}

void MacDemoPhysicsCubeEntity::onStop()
{
}

void MacDemoPhysicsCubeEntity::onDestruct()
{
}