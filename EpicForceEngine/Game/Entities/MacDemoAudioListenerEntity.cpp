///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoAudioListenerEntity.h"
using namespace Magnum;

MacDemoAudioListenerEntity::MacDemoAudioListenerEntity()
: audioListener(*this)
{
}

MacDemoAudioListenerEntity::~MacDemoAudioListenerEntity()
{
}

bool MacDemoAudioListenerEntity::onConstruct()
{
	return true;
}

void MacDemoAudioListenerEntity::onStart()
{
}

void MacDemoAudioListenerEntity::onPause()
{
}

void MacDemoAudioListenerEntity::onResume()
{
}

void MacDemoAudioListenerEntity::onUpdate(float dt)
{
}

void MacDemoAudioListenerEntity::onStop()
{
}

void MacDemoAudioListenerEntity::onDestruct()
{
}

void MacDemoAudioListenerEntity::disableAudio()
{
	//audioListener.disable();
}

void MacDemoAudioListenerEntity::enableAudio()
{
	//audioListener.enable();
}

bool MacDemoAudioListenerEntity::isAudioEnable() const
{
	//return audioListener.isEnable();
	return true;
}