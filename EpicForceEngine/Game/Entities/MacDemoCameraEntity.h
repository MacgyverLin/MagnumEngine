///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoCameraEntity_h_
#define _MacDemoCameraEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoCameraEntity : public Entity
{
public:
	MacDemoCameraEntity();
	virtual ~MacDemoCameraEntity();

	DECLARE_ENTITY(MacDemoCameraEntity);
public:
	/////////////////////////////////////////////////////
	// method
	PerspectiveCameraComponent &getCamera();
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

	void touchpadEvent(const Input::TouchpadEvent &evt);
	void keypadEvent(const Input::GamepadEvent &evt);
	void acceleratorEvent(const Input::AcceleratorEvent &evt);

/////////////////////////////////////////////////////
public:
protected:
private:
	Input::TouchpadMethod<MacDemoCameraEntity>		touchpadMethod;
	Input::GamepadMethod<MacDemoCameraEntity>		keypadMethod;
	Input::AcceleratorMethod<MacDemoCameraEntity>	acceleratorMethod;

	PerspectiveCameraComponent						perspCamera;
	//OrthographicCameraComponent						orthoCamera;
};

#endif