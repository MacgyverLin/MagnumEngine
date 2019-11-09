///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "AudioListenerBase.h"
using namespace Magnum;

AudioListenerBase::AudioListenerBase(Component::Owner &owner_)
: AudioComponent(owner_)
{
	Audio::Manager::instance().audioListeners.push() = this;
}

AudioListenerBase::~AudioListenerBase()
{
	int idx = Audio::Manager::instance().audioListeners.search(this);
	if(idx>=0)
	{
		Audio::Manager::instance().audioListeners.remove(idx);
	}
}