///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoParticleEmitterEntity_h_
#define _MacDemoParticleEmitterEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoParticleEmitterEntity : public Entity
{
public:
	MacDemoParticleEmitterEntity();
	virtual ~MacDemoParticleEmitterEntity();

	DECLARE_ENTITY(MacDemoParticleEmitterEntity);
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
	Input::GamepadMethod<MacDemoParticleEmitterEntity>		keypadMethod;
	void keypadEvent(const Input::GamepadEvent &evt);
public:
protected:
private:
	ParticleEmitterRenderer	particleEmitterRenderer;
	ParticleEmitter					particleEmitter;
};

#endif