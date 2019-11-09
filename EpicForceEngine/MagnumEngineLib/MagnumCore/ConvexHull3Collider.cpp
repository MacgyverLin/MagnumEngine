///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "ConvexHull3Collider.h"
using namespace Magnum;

ConvexHull3Collider::ConvexHull3Collider(Component::Owner &owner_)
: Physics3::RigidBody(owner_)
, type(Physics3::RigidBody::DYNAMIC)
, material()
, collisionFilter()
{
}

ConvexHull3Collider::~ConvexHull3Collider()
{
}

bool ConvexHull3Collider::onConstruct()
{
	//if( !convexHullShape3.construct(vertex, numVertices) )
		//return false;

	if( !constructRigidBody(type, &convexHullShape3, material, collisionFilter) )
		return false;
	
	setTransform(this->getOwner().getGlobalTransform());

	return true;
}

void ConvexHull3Collider::onStart()
{
}

void ConvexHull3Collider::onUpdate(float dt)
{
	updateRigidBody(dt);
}

void ConvexHull3Collider::onPause()
{
}

void ConvexHull3Collider::onResume()
{
}

void ConvexHull3Collider::onStop()
{
}

void ConvexHull3Collider::onDestruct()
{
	convexHullShape3.destruct();
	
	destructRigidBody();
}

void ConvexHull3Collider::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 0.0, 0.5), 
								Vector3(0.5, 0.5, 0.5));

	const AABB3 &aabb = convexHullShape3.getBoundingBox();
	debugRenderer.renderWireBox(getOwner().getGlobalTransform(),
								ColorRGBA(1.0, 1.0, 1.0, 0.5), 
								Vector3(aabb.Max-aabb.Min) * 0.5);
}