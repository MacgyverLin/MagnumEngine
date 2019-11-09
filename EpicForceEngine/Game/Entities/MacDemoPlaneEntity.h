///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoPlaneEntity_h_
#define _MacDemoPlaneEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoPlaneEntity : public Entity
{
public:
	/////////////////////////////////////////////////////////////
	MacDemoPlaneEntity();
	virtual ~MacDemoPlaneEntity();

	DECLARE_ENTITY(MacDemoPlaneEntity);
	/////////////////////////////////////////////////////////////

	PROPERTY(ResourcePath,	Texture0Path);
	/////////////////////////////////////////////////////////////
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
	float t;
	Vector3 initPosition;
	SkeletalAnimModelRenderer		skeletalAnimModelRenderer;
	SkeletalAnimModelComponent		skeletalAnimModelComponent;
	SkeletalAnimBlender				skeletalAnimBlender;
	SkeletalAnimation				animation;
};

#endif