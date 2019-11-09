///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoAudioSourceEntity.h"
using namespace Magnum;

MacDemoAudioSourceEntity::MacDemoAudioSourceEntity()
: audioClip(*this)
{
}

MacDemoAudioSourceEntity::~MacDemoAudioSourceEntity()
{
}

bool MacDemoAudioSourceEntity::onConstruct()
{
	return true;
}

void MacDemoAudioSourceEntity::onStart()
{
	audioClip.play(true);
}

void MacDemoAudioSourceEntity::onPause()
{
}

void MacDemoAudioSourceEntity::onResume()
{
}

void MacDemoAudioSourceEntity::onUpdate(float dt)
{
}

void MacDemoAudioSourceEntity::onStop()
{
}

void MacDemoAudioSourceEntity::onDestruct()
{
}

void MacDemoAudioSourceEntity::disableAudio()
{
}

void MacDemoAudioSourceEntity::enableAudio()
{
}

bool MacDemoAudioSourceEntity::isAudioEnable() const
{
	return true;
}