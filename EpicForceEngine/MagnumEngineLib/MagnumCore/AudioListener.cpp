///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "AudioListener.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace Magnum;

AudioListener::AudioListener(Component::Owner &owner_)
: AudioListenerBase(owner_)
{
}

AudioListener::~AudioListener()
{
}

bool AudioListener::onConstruct()
{
	return true;
}

void AudioListener::onStart()
{
}

void AudioListener::onUpdate(float dt)
{
}

void AudioListener::onPause()
{
}

void AudioListener::onResume()
{
}

void AudioListener::onStop()
{
}

void AudioListener::onDestruct()
{
}

void AudioListener::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 0.0, 1.0, 0.5), 
								Vector3(1, 1, 1));
}