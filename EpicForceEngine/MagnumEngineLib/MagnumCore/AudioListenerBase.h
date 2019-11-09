///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioListenerBase_h_
#define _AudioListenerBase_h_

#include "Stage.h"
#include "Audio.h"
#include "AudioComponent.h"
using namespace Magnum;

namespace Magnum
{

/**
* AudioListenerBase.
* AudioListenerBase is the base class of all Audio Listener component.
* @see AudioComponent
*/
class AudioListenerBase : public AudioComponent
{
friend class Audio::Manager;
public:
////////////////////////////////////////////////////////////////
	/**
	* AudioListenerBase Constructor.
	* To Construct the AudioListenerBase for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	AudioListenerBase(Component::Owner &owner_);

	/**
	* AudioListenerBase Destructor.
	* To Destruct AudioListenerBase and remove from its owner.
	*/
	virtual ~AudioListenerBase();
////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(AudioListenerBase, AudioComponent, false)

////////////////////////////////////////////////////////////////
protected:
private:


////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif