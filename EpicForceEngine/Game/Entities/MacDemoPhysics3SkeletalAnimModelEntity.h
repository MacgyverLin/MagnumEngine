///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoPhysics3SkeletalAnimModelEntity_h_
#define _MacDemoPhysics3SkeletalAnimModelEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoPhysics3SkeletalAnimModelEntity : public Entity
{
public:
//////////////////////////////////////////////////////////////
	MacDemoPhysics3SkeletalAnimModelEntity();
	virtual ~MacDemoPhysics3SkeletalAnimModelEntity();

	DECLARE_ENTITY(MacDemoPhysics3SkeletalAnimModelEntity);
//////////////////////////////////////////////////////////////
	PROPERTY(Vector3,	InitialVelocity);
//////////////////////////////////////////////////////////////
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

	/////////////////////////////////////////////////////
public:
protected:
private:
	SkeletalAnimModelRenderer		skeletalAnimModelRenderer;
	SkeletalAnimModelComponent		skeletalAnimModelComponent;
	SkeletalAnimBlender				skeletalAnimBlender;
	SkeletalAnimation				animation;

	Box3Collider					collider;
	//BVHTriangleMeshCollider		collider;
	//Capsule3Collider				collider;
	//Cone3Collider					collider;
	//ConvexHull3Collider			collider;
	//Cylinder3Collider				collider;
	//HeightFieldCollider			collider;
	//SphereCollider				collider;
};

#endif