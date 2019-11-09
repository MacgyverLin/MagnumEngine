///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoParticleEmitterEntity.h"
using namespace Magnum;

MacDemoParticleEmitterEntity::MacDemoParticleEmitterEntity()
: particleEmitterRenderer(*this)
, particleEmitter(*this)
, keypadMethod(this, &MacDemoParticleEmitterEntity::keypadEvent)
{
	particleEmitterRenderer.add(particleEmitter);
}

MacDemoParticleEmitterEntity::~MacDemoParticleEmitterEntity()
{
	particleEmitterRenderer.remove(particleEmitter);
}

bool MacDemoParticleEmitterEntity::onConstruct()
{
	return true;
}

void MacDemoParticleEmitterEntity::onStart()
{
}

void MacDemoParticleEmitterEntity::onPause()
{
}

void MacDemoParticleEmitterEntity::onResume()
{
}

void MacDemoParticleEmitterEntity::onUpdate(float dt)
{
}

void MacDemoParticleEmitterEntity::onStop()
{
}

void MacDemoParticleEmitterEntity::onDestruct()
{
}

void MacDemoParticleEmitterEntity::keypadEvent(const Input::GamepadEvent &evt)
{
	if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
	{
		if(evt.keyCode==Input::KEYPAD0_UP)
		{
			if(particleEmitter.getEmitting())
				particleEmitter.setEmitting(false);
			else
				particleEmitter.setEmitting(true);
		}
	}
}
