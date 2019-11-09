///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoLevelEntity.h"
using namespace Magnum;

MacDemoLevelEntity::MacDemoLevelEntity()
: skeletalAnimModelRenderer(*this)
, skeletalAnimModelComponent(*this)
{
	skeletalAnimModelComponent.setModelPath(ResourcePath("demo/level1", "skelanimmdl"));

	skeletalAnimModelRenderer.add(skeletalAnimModelComponent);
}

MacDemoLevelEntity::~MacDemoLevelEntity()
{
	skeletalAnimModelRenderer.remove(skeletalAnimModelComponent);
}

bool MacDemoLevelEntity::onConstruct()
{
	VisualEffect *effect = skeletalAnimModelComponent.getVisualEffect(0);
	
	if(effect)
	{
		int localBBoxMinIdx = effect->getUniformHandle("localBBoxMin");
		effect->setValue(localBBoxMinIdx, Vector3(-10.0, 0.0, -25.0));
		int localBBoxMaxIdx = effect->getUniformHandle("localBBoxMax");
		effect->setValue(localBBoxMaxIdx, Vector3( 10.0, 0.0,  25.0));
		int texturePatchPerUnit1Idx = effect->getUniformHandle("texturePatchPerUnit1");
		effect->setValue(texturePatchPerUnit1Idx, 1.0f);
		int texturePatchPerUnit2Idx = effect->getUniformHandle("texturePatchPerUnit2");
		effect->setValue(texturePatchPerUnit2Idx, 1.0f);
	}

	return true;
}

void MacDemoLevelEntity::onStart()
{
}

void MacDemoLevelEntity::onPause()
{
}

void MacDemoLevelEntity::onResume()
{
}

void MacDemoLevelEntity::onUpdate(float dt)
{
}

void MacDemoLevelEntity::onStop()
{
}

void MacDemoLevelEntity::onDestruct()
{
}