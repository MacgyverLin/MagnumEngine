///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioListener_h_
#define _AudioListener_h_

#include "Stage.h"
#include "Audio.h"
#include "AudioListenerBase.h"
using namespace Magnum;

namespace Magnum
{

/**
* AudioListener.
* AudioListener is the class resposible for audio received
* @see AudioListenerBase
*/
class AudioListener : public AudioListenerBase
{
friend class Audio::Manager;
public:
////////////////////////////////////////////////////////////////
	AudioListener(Component::Owner &owner_);
	virtual ~AudioListener();

////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(AudioListener, AudioListenerBase, false)

////////////////////////////////////////////////////////////////
public:
protected:
private:
	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct();

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart();

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt);

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause();

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume();

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop();

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif