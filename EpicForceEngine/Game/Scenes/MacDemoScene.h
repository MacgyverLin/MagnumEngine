///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoScene_h_
#define _MacDemoScene_h_

#include <MagnumEngine.h>
#include <MagnumGame.h>
using namespace Magnum;

class MacDemoScene : public BasicScene
{
public:
	enum State
	{
		START = 0,
		LOAD,
		CHECKING_RAWASSETS,
		UPDATING_ASSETS,
		VALIDATE_ENTITIES,
		MAIN,
	};

	MacDemoScene();
	virtual ~MacDemoScene();

	virtual void onConstruct();								//	called after all constructors
	virtual void onEnter();									//	called after enter transition is done
	virtual void onExit();									//	called before exit transition starts
	virtual void onUpdate(float dt);						//	called each cycle while scene is up and running
	virtual void onPause();									//	called when about to paused
	virtual void onResume();								//	called when about to resume
	virtual bool onTransition(TransitionMode);				//	called while transitioning returning false stops transition mode

	void touchpadEvent(const Input::TouchpadEvent &evt);
	void keypadEvent(const Input::GamepadEvent &evt);
	void acceleratorEvent(const Input::AcceleratorEvent &evt);
private:
	Input::TouchpadMethod<MacDemoScene>		touchpadMethod;
	Input::GamepadMethod<MacDemoScene>		keypadMethod;
	Input::AcceleratorMethod<MacDemoScene>	acceleratorMethod;

	void updateCamera();
	
	Array<MacDemoCameraEntity						*>	macDemoCameras;
	Array<MacDemoPlaneEntity						*>	macDemoPlaneEntities;	
	MacDemoSkySphereEntity							*	macDemoSkySphere;
	MacDemoAudioSourceEntity						*   macDemoAudioSourceEntity;
	MacDemoBGMEntity								*   macDemoBGMEntity;
	MacDemoLevelEntity								*	macDemoLevelEntity;	
	MacDemoAudioListenerEntity						*   macDemoAudioListenerEntity;
	MacDemoBillBoardEntity							*	macDemoBillBoardEntity;
	MacDemoCubeEntity								*	macDemoCubeEntity;
	MacDemoDiffuseMapCubeEntity						*	macDemoDiffuseMapCubeEntity;
	MacDemoDiffuseMapSpecularMapCubeEntity			*	macDemoDiffuseMapSpecularMapCubeEntity;
	MacDemoParticleEmitterEntity					*	macDemoParticleEmitterEntity;
	MacDemoPhysics3SkeletalAnimModelEntity			*	macDemoPhysics3SkeletalAnimModelEntity;

	State						state;
	
	Vector2						mouseDownPosition;
	float						phi, oldPhi;
	float						theta, oldTheta;
	float						radius, oldRadius;
	Vector3						cameraPosition;

	int							mode;

	float						angle;
	Vector3						velocity;
};

#endif