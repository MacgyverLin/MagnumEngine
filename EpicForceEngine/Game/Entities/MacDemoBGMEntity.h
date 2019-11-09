///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoBGMEntity_h_
#define _MacDemoBGMEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoBGMEntity : public Entity
{
public:
	MacDemoBGMEntity();
	virtual ~MacDemoBGMEntity();

	DECLARE_ENTITY(MacDemoBGMEntity);

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
	AudioStream					audioStream;
};

#endif