///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoCubeEntity.h"
using namespace Magnum;

MacDemoCubeEntity::MacDemoCubeEntity()
: cubeRenderer(*this)
, cube(*this)
{
	cubeRenderer.add(cube);
}

MacDemoCubeEntity::~MacDemoCubeEntity()
{
	cubeRenderer.remove(cube);
}

bool MacDemoCubeEntity::onConstruct()
{
	return true;
}

void MacDemoCubeEntity::onStart()
{
}

void MacDemoCubeEntity::onPause()
{
}

void MacDemoCubeEntity::onResume()
{
}

void MacDemoCubeEntity::onUpdate(float dt)
{
}

void MacDemoCubeEntity::onStop()
{
}

void MacDemoCubeEntity::onDestruct()
{
}