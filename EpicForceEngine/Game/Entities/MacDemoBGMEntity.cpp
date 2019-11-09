///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoBGMEntity.h"
using namespace Magnum;

MacDemoBGMEntity::MacDemoBGMEntity()
: audioStream(*this)
{
}

MacDemoBGMEntity::~MacDemoBGMEntity()
{
}

bool MacDemoBGMEntity::onConstruct()
{
	return true;
}

void MacDemoBGMEntity::onStart()
{
	audioStream.play(true);
}

void MacDemoBGMEntity::onPause()
{
}

void MacDemoBGMEntity::onResume()
{
}

void MacDemoBGMEntity::onUpdate(float dt)
{
}

void MacDemoBGMEntity::onStop()
{
}

void MacDemoBGMEntity::onDestruct()
{
}

void MacDemoBGMEntity::disableAudio()
{
}

void MacDemoBGMEntity::enableAudio()
{
}

bool MacDemoBGMEntity::isAudioEnable() const
{
    return true;
}