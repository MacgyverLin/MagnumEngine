///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "HeightFieldCollider.h"
using namespace Magnum;

HeightFieldCollider::HeightFieldCollider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
}

HeightFieldCollider::~HeightFieldCollider()
{
}

bool HeightFieldCollider::onConstruct()
{
	//if( !heightFieldShape3.construct() )
		//return false;

	if( !constructRigidBody(Physics3::RigidBody::STATIC, &heightFieldShape3, material, collisionFilter) )
		return false;
	
	setTransform(getOwner().getGlobalTransform());

	return true;
}

void HeightFieldCollider::onStart()
{
}

void HeightFieldCollider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void HeightFieldCollider::onPause()
{
}

void HeightFieldCollider::onResume()
{
}

void HeightFieldCollider::onStop()
{
}

void HeightFieldCollider::onDestruct()
{
	heightFieldShape3.destruct();
	
	destructRigidBody();
}

void HeightFieldCollider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								Vector3(0.5, 0.5, 0.5));

	const AABB3 &aabb = heightFieldShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}