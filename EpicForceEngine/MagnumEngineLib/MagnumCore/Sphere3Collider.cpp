///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Sphere3Collider.h"
using namespace Magnum;

Sphere3Collider::Sphere3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setRadius(0.5);
}

Sphere3Collider::~Sphere3Collider()
{
}

bool Sphere3Collider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	if( !sphereShape3.construct(getRadius()) )
		return false;

	if( !constructRigidBody(type, &sphereShape3, material, collisionFilter) )
		return false;
	
	setTransform(getOwner().getGlobalTransform());

	return true;
}

void Sphere3Collider::onStart()
{
}

void Sphere3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void Sphere3Collider::onPause()
{
}

void Sphere3Collider::onResume()
{
}

void Sphere3Collider::onStop()
{
}

void Sphere3Collider::onDestruct()
{
	sphereShape3.destruct();
	
	destructRigidBody();
}

void Sphere3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireSphere(getOwner().getGlobalTransform(),
								   ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								   getRadius(), 5, 5);

	const AABB3 &aabb = sphereShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}