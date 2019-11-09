///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Cone3Collider.h"
using namespace Magnum;

Cone3Collider::Cone3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setRadius(0.5);
	setHeight(1);
}

Cone3Collider::~Cone3Collider()
{
}

bool Cone3Collider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	if( !coneShape3.construct(ConeShape3::Y_AXIS, getRadius(), getHeight()) )
		return false;

	if( !constructRigidBody(type, &coneShape3, material, collisionFilter) )
		return false;
	
	setTransform(this->getOwner().getGlobalTransform());

	return true;
}

void Cone3Collider::onStart()
{
}

void Cone3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void Cone3Collider::onPause()
{
}

void Cone3Collider::onResume()
{
}

void Cone3Collider::onStop()
{
}

void Cone3Collider::onDestruct()
{
	coneShape3.destruct();
	
	destructRigidBody();
}

void Cone3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireCone(getOwner().getGlobalTransform(),
								 ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								 getRadius(), getHeight(), 4, 3);

	const AABB3 &aabb = coneShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}