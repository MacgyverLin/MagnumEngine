///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoDiffuseMapSpecularMapCubeEntity.h"
using namespace Magnum;

MacDemoDiffuseMapSpecularMapCubeEntity::MacDemoDiffuseMapSpecularMapCubeEntity()
: diffuseMapSpecularMapCubeRenderer(*this)
, diffuseMapSpecularMapCube(*this)
{
	diffuseMapSpecularMapCubeRenderer.add(diffuseMapSpecularMapCube);
}

MacDemoDiffuseMapSpecularMapCubeEntity::~MacDemoDiffuseMapSpecularMapCubeEntity()
{
	diffuseMapSpecularMapCubeRenderer.remove(diffuseMapSpecularMapCube);
}

bool MacDemoDiffuseMapSpecularMapCubeEntity::onConstruct()
{
	return true;
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onStart()
{
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onStop()
{
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onUpdate(float dt)
{
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onPause()
{
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onResume()
{
}

void MacDemoDiffuseMapSpecularMapCubeEntity::onDestruct()
{
}