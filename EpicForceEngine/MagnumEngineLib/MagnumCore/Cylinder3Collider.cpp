///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Cylinder3Collider.h"
using namespace Magnum;

Cylinder3Collider::Cylinder3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setRadius(0.5);
	setHeight(1);
}

Cylinder3Collider::~Cylinder3Collider()
{
}

bool Cylinder3Collider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	if( !cylinderShape3.construct(CylinderShape3::Y_AXIS, getRadius(), getHeight()) )
		return false;

	if( !constructRigidBody(type, &cylinderShape3, material, collisionFilter) )
		return false;
	
	setTransform(getOwner().getGlobalTransform());

	return true;
}

void Cylinder3Collider::onStart()
{
}

void Cylinder3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void Cylinder3Collider::onPause()
{
}

void Cylinder3Collider::onResume()
{
}

void Cylinder3Collider::onStop()
{
}

void Cylinder3Collider::onDestruct()
{
	cylinderShape3.destruct();
	
	destructRigidBody();
}

void Cylinder3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireSphere(getOwner().getGlobalTransform(),
								   ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								   getRadius(), 4, 3);

	const AABB3 &aabb = cylinderShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}