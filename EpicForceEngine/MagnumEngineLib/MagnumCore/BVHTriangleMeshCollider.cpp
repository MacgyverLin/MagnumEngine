///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BVHTriangleMeshCollider.h"
using namespace Magnum;

BVHTriangleMeshCollider::BVHTriangleMeshCollider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
	setColliderPath(ResourcePath("default/default", "bvhtrimesh"));
}

BVHTriangleMeshCollider::~BVHTriangleMeshCollider()
{
}

bool BVHTriangleMeshCollider::onConstruct()
{
	if(getStatic())
		type = Physics3::RigidBody::STATIC;
	else
		type = Physics3::RigidBody::DYNAMIC;

	// mesh data
	if( !bvhTriangleMeshShape3.construct(getColliderPath().getPath()) )
		return false;

	if( !constructRigidBody(type, &bvhTriangleMeshShape3, material, collisionFilter) )
		return false;
	
	setTransform(this->getOwner().getGlobalTransform());

	return true;
}

void BVHTriangleMeshCollider::onStart()
{
}

void BVHTriangleMeshCollider::onUpdate(float dt)
{
	// updateRigidBody(dt);
}

void BVHTriangleMeshCollider::onPause()
{
}

void BVHTriangleMeshCollider::onResume()
{
}

void BVHTriangleMeshCollider::onStop()
{
}

void BVHTriangleMeshCollider::onDestruct()
{
	bvhTriangleMeshShape3.destruct();
	
	destructRigidBody();
}

void BVHTriangleMeshCollider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	//bvhTriangleMeshShape3.debugRender(getOwner().getGlobalTransform(), debugRenderer);
}