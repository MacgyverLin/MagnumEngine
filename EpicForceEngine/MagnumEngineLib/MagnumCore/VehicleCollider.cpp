///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "VehicleCollider.h"
using namespace Magnum;

VehicleCollider::VehicleCollider(Component::Owner &owner_)
: Physics3::Vehicle(owner_)
, material()
, collisionFilter()
{
}

VehicleCollider::~VehicleCollider()
{
}

bool VehicleCollider::onConstruct()
{
	material.density = 800.0f / 21.0f;
	if( !constructRigidBody(material, collisionFilter) )
		return false;
	
	setTransform(getOwner().getGlobalTransform());

	return true;
}

void VehicleCollider::onStart()
{
}

void VehicleCollider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void VehicleCollider::onPause()
{
}

void VehicleCollider::onResume()
{
}

void VehicleCollider::onStop()
{
}

void VehicleCollider::onDestruct()
{
	destructRigidBody();
}

void VehicleCollider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
}