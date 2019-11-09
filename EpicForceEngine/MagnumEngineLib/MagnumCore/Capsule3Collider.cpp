///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Capsule3Collider.h"
using namespace Magnum;

Capsule3Collider::Capsule3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setRadius(0.5);
	setHeight(1);
}

Capsule3Collider::~Capsule3Collider()
{
}

bool Capsule3Collider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	if( !capsuleShape3.construct(CapsuleShape3::Y_AXIS, getRadius(), getHeight()) )
		return false;

	if( !constructRigidBody(type, &capsuleShape3, material, collisionFilter) )
		return false;
	
	setTransform(this->getOwner().getGlobalTransform());

	return true;
}

void Capsule3Collider::onStart()
{
}

void Capsule3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void Capsule3Collider::onPause()
{
}

void Capsule3Collider::onResume()
{
}

void Capsule3Collider::onStop()
{
}

void Capsule3Collider::onDestruct()
{
	capsuleShape3.destruct();
	
	destructRigidBody();
}

void Capsule3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireCapsule(getOwner().getGlobalTransform(),
								    ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								    getRadius(), getHeight(), 4, 3);

	const AABB3 &aabb = capsuleShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}