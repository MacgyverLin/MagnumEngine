///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Box3Collider.h"
using namespace Magnum;

Box3Collider::Box3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setExtent(Vector3(0.5, 0.5, 0.5));
}

Box3Collider::~Box3Collider()
{
}

bool Box3Collider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	Vector3 extent(getExtent());
	if( !boxShape3.construct(extent) )
		return false;

	if( !constructRigidBody(type, &boxShape3, material, collisionFilter) )
		return false;
	
	setTransform(getOwner().getGlobalTransform());

	return true;
}

void Box3Collider::onStart()
{
}

void Box3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void Box3Collider::onPause()
{
}

void Box3Collider::onResume()
{
}

void Box3Collider::onStop()
{
}

void Box3Collider::onDestruct()
{
	boxShape3.destruct();
	
	destructRigidBody();
}

void Box3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								getExtent());

	const AABB3 &aabb = boxShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}