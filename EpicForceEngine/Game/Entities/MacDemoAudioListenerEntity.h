///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoAudioListenerEntity_h_
#define _MacDemoAudioListenerEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

/**
 *  A test class. A more elaborate class description.
 */
class MacDemoAudioListenerEntity : public Entity
{
public:
	MacDemoAudioListenerEntity();
	virtual ~MacDemoAudioListenerEntity();

	DECLARE_ENTITY(MacDemoAudioListenerEntity);
	
	void disableAudio();
	void enableAudio();
	bool isAudioEnable() const;
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

/////////////////////////////////////////////////////
public:
protected:
private:
	AudioListener				audioListener;
};

#endif