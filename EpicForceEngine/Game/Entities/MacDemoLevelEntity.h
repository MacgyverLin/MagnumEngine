///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoLevelEntity_h_
#define _MacDemoLevelEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoLevelEntity : public Entity
{
public:
	MacDemoLevelEntity();
	virtual ~MacDemoLevelEntity();

	DECLARE_ENTITY(MacDemoLevelEntity);
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
};

#endif