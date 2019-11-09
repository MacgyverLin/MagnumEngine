///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioComponent_h_
#define _AudioComponent_h_

#include "Stage.h"
#include "Audio.h"
#include "Component.h"
using namespace Magnum;

namespace Magnum
{

/**
* AudioComponent.
* AudioComponent is the base class of all Audio related component.
* @see Component
*/
class AudioComponent : public Component
{
friend class Audio::Manager;
public:
////////////////////////////////////////////////////////////////
	/**
	* AudioComponent Constructor.
	* To Construct the AudioComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	AudioComponent(Component::Owner &owner_);

	/**
	* AudioComponent Destructor.
	* To Destruct AudioComponent and remove from its owner.
	*/
	virtual ~AudioComponent();
////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(AudioComponent, Component, false)

////////////////////////////////////////////////////////////////
protected:
	/**
	* Get the handle for BGM Channel Group.
	* Audio is divided in 2 groups for convenient management. They are the BGM Group and the SFX Group.
	* @return void *, the BGM Group Handle.
	*/
	void *getBGMChannelGroupHandle();

	/**
	* Get the handle for SFX Channel Group.
	* Audio is divided in 2 groups for convenient management. They are the BGM Group and the SFX Group.
	* @return void *, the SFX Group Handle.
	*/
	void *getSFXChannelGroupHandle();

	/**
	* Get the handle for audio system.
	* @return void *, the audio system Handle.
	*/
	void *getSystemHandle();
private:


////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif