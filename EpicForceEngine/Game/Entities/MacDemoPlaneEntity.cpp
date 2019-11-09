///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoPlaneEntity.h"
using namespace Magnum;

MacDemoPlaneEntity::MacDemoPlaneEntity()
: skeletalAnimModelRenderer(*this)
, skeletalAnimModelComponent(*this)
, initPosition(Vector3::ZERO)
, t(0)
{
	skeletalAnimModelComponent.setModelPath(ResourcePath("demo/f14/f14", "skelanimmdl"));
	setTexture0Path(ResourcePath("demo/texture/f14", "texture"));

	skeletalAnimModelRenderer.add(skeletalAnimModelComponent);
}

MacDemoPlaneEntity::~MacDemoPlaneEntity()
{
	skeletalAnimModelRenderer.remove(skeletalAnimModelComponent);
}

bool MacDemoPlaneEntity::onConstruct()
{
	if( !animation.construct(skeletalAnimModelComponent.getModelPath().getPath()) )
		return false;

	animation.setSpeed(1);
	animation.setLoopBehavior(AnimBase::PINGPONG);
	skeletalAnimBlender.initSkeleton(&animation);
	skeletalAnimBlender.addAnimation(&animation);
	skeletalAnimModelComponent.setAnimation(&skeletalAnimBlender);

	VisualEffect *effect = skeletalAnimModelComponent.getVisualEffect(0);
	if(effect)
	{
		int ambientLightColorIdx = effect->getUniformHandle("ambientLightColor");
		effect->setValue(ambientLightColorIdx, Vector4(0.7, 0.7, 0.7, 1));
	}

	return true;
}

void MacDemoPlaneEntity::onStart()
{
	initPosition = this->getGlobalPosition();
	t = Math::IntervalRandom(0, 5);

	skeletalAnimBlender.play();
}

void MacDemoPlaneEntity::onPause()
{
}

void MacDemoPlaneEntity::onResume()
{
}

void MacDemoPlaneEntity::onUpdate(float dt)
{
	t += dt;

	//if(this->getBehaviour()==0)
	{
		Vector3 pos = initPosition + Vector3(0.4*Math::Sin(t * Math::TWO_PI / 10), Math::Sin(t * Math::TWO_PI / 5), 0.2*Math::Sin(t * Math::TWO_PI / 10));
		
		Matrix4 transform;
		transform.initTranslateRotZXYScale(pos.X(), pos.Y(), pos.Z(), 0, 0, 0, 1);

		setLocalTransform(transform);
	}
	
	skeletalAnimBlender.update();
}

void MacDemoPlaneEntity::onStop()
{
}

void MacDemoPlaneEntity::onDestruct()
{
	animation.destruct();
}