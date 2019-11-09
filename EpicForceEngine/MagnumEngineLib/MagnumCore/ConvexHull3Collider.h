///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _ConvexHull3Collider_h_
#define _ConvexHull3Collider_h_

#include "Stage.h"
#include "Physics3.h"
#include "ConvexHullShape3.h"
using namespace EpicForce;

namespace Magnum
{

class ConvexHull3Collider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	ConvexHull3Collider(Component::Owner &owner_);
	~ConvexHull3Collider();

	DECLARE_COMPONENT(ConvexHull3Collider, Physics3::RigidBody, false)
public:
	Physics3::RigidBody::Type	type;
	Physics3::Material			material;
	Physics3::CollisionFilter	collisionFilter;
////////////////////////////////////////////////////////////////
public:
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onUpdate(float dt);
	virtual void onPause();
	virtual void onResume();
	virtual void onStop();
	virtual void onDestruct();
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
///////////////////////////////////////////////////////////////////
public:
protected:
private:
	ConvexHullShape3 convexHullShape3;
};

};

#endif
