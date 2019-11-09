///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "AudioComponent.h"
using namespace Magnum;

AudioComponent::AudioComponent(Component::Owner &owner_)
: Component(owner_)
{
}

AudioComponent::~AudioComponent()
{
}

void *AudioComponent::getBGMChannelGroupHandle()
{
	return Audio::Manager::instance().getBGMChannelGroupHandle();
}

void *AudioComponent::getSFXChannelGroupHandle()
{
	return Audio::Manager::instance().getSFXChannelGroupHandle();
}

void *AudioComponent::getSystemHandle()
{
	return Audio::Manager::instance().getSystemHandle();
}