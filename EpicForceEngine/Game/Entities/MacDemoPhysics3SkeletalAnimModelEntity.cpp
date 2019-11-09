///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoPhysics3SkeletalAnimModelEntity.h"
using namespace Magnum;

MacDemoPhysics3SkeletalAnimModelEntity::MacDemoPhysics3SkeletalAnimModelEntity()
: skeletalAnimModelRenderer(*this)
, skeletalAnimModelComponent(*this)
, collider(*this)
{
	setInitialVelocity(Vector3::ZERO);

	//skeletalAnimModelComponent.modelPath.setPath("default/default");
	skeletalAnimModelRenderer.add(skeletalAnimModelComponent);
}

MacDemoPhysics3SkeletalAnimModelEntity::~MacDemoPhysics3SkeletalAnimModelEntity()
{
	skeletalAnimModelRenderer.remove(skeletalAnimModelComponent);
}

bool MacDemoPhysics3SkeletalAnimModelEntity::onConstruct()
{
	if( !animation.construct(skeletalAnimModelComponent.getModelPath().getPath()) )
		return false;

	animation.setSpeed(10);
	animation.setLoopBehavior(AnimBase::PINGPONG);
	skeletalAnimBlender.initSkeleton(&animation);
	skeletalAnimBlender.addAnimation(&animation);
	skeletalAnimModelComponent.setAnimation(&skeletalAnimBlender);

	collider.setType(getStatic() ? Physics3::RigidBody::STATIC : Physics3::RigidBody::DYNAMIC);
	collider.setTransform(getGlobalTransform());
	collider.setLinearVelocity(getInitialVelocity());
	
	return true;
}

void MacDemoPhysics3SkeletalAnimModelEntity::onStart()
{
	skeletalAnimBlender.play();
}

void MacDemoPhysics3SkeletalAnimModelEntity::onPause()
{
}

void MacDemoPhysics3SkeletalAnimModelEntity::onResume()
{
}

void MacDemoPhysics3SkeletalAnimModelEntity::onUpdate(float dt)
{
	animation.update();
}

void MacDemoPhysics3SkeletalAnimModelEntity::onStop()
{
}

void MacDemoPhysics3SkeletalAnimModelEntity::onDestruct()
{
	animation.destruct();
}