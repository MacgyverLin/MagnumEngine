///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoDiffuseMapCubeEntity.h"
using namespace Magnum;

MacDemoDiffuseMapCubeEntity::MacDemoDiffuseMapCubeEntity()
: diffuseMapCubeRenderer(*this)
, diffuseMapCube(*this)
{
	diffuseMapCubeRenderer.add(diffuseMapCube);
}

MacDemoDiffuseMapCubeEntity::~MacDemoDiffuseMapCubeEntity()
{
	diffuseMapCubeRenderer.remove(diffuseMapCube);
}

bool MacDemoDiffuseMapCubeEntity::onConstruct()
{
	return true;
}

void MacDemoDiffuseMapCubeEntity::onStart()
{
}

void MacDemoDiffuseMapCubeEntity::onPause()
{
}

void MacDemoDiffuseMapCubeEntity::onResume()
{
}

void MacDemoDiffuseMapCubeEntity::onUpdate(float dt)
{
}

void MacDemoDiffuseMapCubeEntity::onStop()
{
}

void MacDemoDiffuseMapCubeEntity::onDestruct()
{
}