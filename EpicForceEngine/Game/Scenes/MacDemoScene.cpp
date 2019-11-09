///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoScene.h"
using namespace Magnum;

namespace
{
#if 0
#define NUM_MODELS (12)
const char *filenames[] = 
{
	"demo/a4",
	"demo/a10",
	"demo/f4",
	"demo/ef2000",
	"demo/f14",
	"demo/su25",
	"testRig/adawong/adawong",
	"testRig/adawong2/adawong2",
	"testRig/jill/jill",
	"demo/f16",
	"demo/kfc7",
	"demo/f18",
};

#else

#define NUM_MODELS (12-3)
const char *filenames[] = 
{
	"demo/a4",
	"demo/a10",
	"demo/f4",
	"demo/ef2000",
	"demo/f14",
	"demo/su25",
	/*
	"testRig/adawong/adawong",
	"testRig/adawong2/adawong2",
	"testRig/jill/jill",
	*/
	"demo/f16",
	"demo/kfc7",
	"demo/f18",
};
#endif
};


MacDemoScene::MacDemoScene()
: touchpadMethod(this, &MacDemoScene::touchpadEvent)
, keypadMethod(this, &MacDemoScene::keypadEvent)
, acceleratorMethod(this, &MacDemoScene::acceleratorEvent)
, state(LOAD)
, macDemoCameras(1)
, macDemoPlaneEntities(NUM_MODELS)
{
	angle = 0;

	mouseDownPosition		= Vector2::ZERO;
	theta					= -0.556324;
	phi						= -0.496328;
	radius					= 0;
	cameraPosition			= Vector3(20, 20, 20);
	
	for(int i=0; i<macDemoCameras.length(); i++)
	{
		macDemoCameras[i] = 0;
	}

	for(int i=0; i<macDemoPlaneEntities.length(); i++)
	{
		macDemoPlaneEntities[i] = 0;
	}

	macDemoSkySphere						= 0;

	macDemoAudioSourceEntity				= 0;
	
	macDemoBGMEntity						= 0;

	macDemoLevelEntity						= 0;

	macDemoAudioListenerEntity				= 0;

	macDemoBillBoardEntity					= 0;
	macDemoCubeEntity						= 0;
	macDemoDiffuseMapCubeEntity				= 0;
	macDemoDiffuseMapSpecularMapCubeEntity	= 0;
	
	macDemoParticleEmitterEntity			= 0;

	macDemoPhysics3SkeletalAnimModelEntity	= 0;

	////////////////////////////////////
	velocity = Vector3::ZERO;
}


MacDemoScene::~MacDemoScene()
{
	for(int i=0; i<macDemoCameras.length(); i++)
	{
		if(macDemoCameras[i])
		{
			Entity::release(macDemoCameras[i]);
			macDemoCameras[i] = 0;
		}
	}

	for(int i=0; i<macDemoPlaneEntities.length(); i++)
	{
		if(macDemoPlaneEntities[i])
		{
			Entity::release(macDemoPlaneEntities[i]);
			macDemoPlaneEntities[i] = 0;
		}
	}

	if(macDemoSkySphere)
	{
		Entity::release(macDemoSkySphere);
		macDemoSkySphere					= 0;
	}

	if(macDemoAudioSourceEntity)
	{
		Entity::release(macDemoAudioSourceEntity);
		macDemoAudioSourceEntity			= 0;
	}

	if(macDemoBGMEntity)
	{
		Entity::release(macDemoBGMEntity);
		macDemoBGMEntity					= 0;
	}

	if(macDemoLevelEntity)
	{
		Entity::release(macDemoLevelEntity);
		macDemoLevelEntity					= 0;
	}

	if(macDemoAudioListenerEntity)
	{
		Entity::release(macDemoAudioListenerEntity);
		macDemoAudioListenerEntity			= 0;
	}

	if(macDemoBillBoardEntity)
	{
		Entity::release(macDemoBillBoardEntity);
		macDemoBillBoardEntity				= 0;
	}

	if(macDemoCubeEntity)
	{
		Entity::release(macDemoCubeEntity);
		macDemoCubeEntity					= 0;
	}

	if(macDemoDiffuseMapCubeEntity)
	{
		Entity::release(macDemoDiffuseMapCubeEntity);
		macDemoDiffuseMapCubeEntity			= 0;
	}

	if(macDemoDiffuseMapSpecularMapCubeEntity)
	{
		Entity::release(macDemoDiffuseMapSpecularMapCubeEntity);
		macDemoDiffuseMapSpecularMapCubeEntity	= 0;
	}

	if(macDemoParticleEmitterEntity)
	{
		Entity::release(macDemoParticleEmitterEntity);
		macDemoParticleEmitterEntity		= 0;
	}

	if(macDemoPhysics3SkeletalAnimModelEntity)
	{
		Entity::release(macDemoPhysics3SkeletalAnimModelEntity);
		macDemoPhysics3SkeletalAnimModelEntity		= 0;
	}
}

//	called after all constructors
void MacDemoScene::onConstruct()
{
}

//	called after enter transition is done
void MacDemoScene::onEnter()
{
}

//	called before exit transition starts
void MacDemoScene::onExit()
{
}

//	called each cycle while scene is up and running
void MacDemoScene::onUpdate(float dt)
{
	switch(state)
	{
	case START:
		//state = EDITOR_MAIN;
		break;

	case LOAD:

		/////////////////////////////////////////////////////////////////////////////////////////
		// release old scene
		for(int i=0; i<macDemoCameras.length(); i++)
		{
			if(macDemoCameras[i])
			{
				Entity::release(macDemoCameras[i]);
				macDemoCameras[i] = 0;
			}
		}

		for(int i=0; i<macDemoPlaneEntities.length(); i++)
		{
			if(macDemoPlaneEntities[i])
			{
				Entity::release(macDemoPlaneEntities[i]);
				macDemoPlaneEntities[i] = 0;
			}
		}

		if(macDemoSkySphere)
		{
			Entity::release(macDemoSkySphere);
			macDemoSkySphere					= 0;
		}

		if(macDemoAudioSourceEntity)
		{
			Entity::release(macDemoAudioSourceEntity);
			macDemoAudioSourceEntity			= 0;
		}

		if(macDemoBGMEntity)
		{
			Entity::release(macDemoBGMEntity);
			macDemoBGMEntity					= 0;
		}

		if(macDemoLevelEntity)
		{
			Entity::release(macDemoLevelEntity);
			macDemoLevelEntity					= 0;
		}

		if(macDemoAudioListenerEntity)
		{
			Entity::release(macDemoAudioListenerEntity);
			macDemoAudioListenerEntity			= 0;
		}

		if(macDemoBillBoardEntity)
		{
			Entity::release(macDemoBillBoardEntity);
			macDemoBillBoardEntity				= 0;
		}

		if(macDemoCubeEntity)
		{
			Entity::release(macDemoCubeEntity);
			macDemoCubeEntity					= 0;
		}

		if(macDemoDiffuseMapCubeEntity)
		{
			Entity::release(macDemoDiffuseMapCubeEntity);
			macDemoDiffuseMapCubeEntity			= 0;
		}

		if(macDemoDiffuseMapSpecularMapCubeEntity)
		{
			Entity::release(macDemoDiffuseMapSpecularMapCubeEntity);
			macDemoDiffuseMapSpecularMapCubeEntity	= 0;
		}

		if(macDemoParticleEmitterEntity)
		{
			Entity::release(macDemoParticleEmitterEntity);
			macDemoParticleEmitterEntity		= 0;
		}

		if(macDemoPhysics3SkeletalAnimModelEntity)
		{
			Entity::release(macDemoPhysics3SkeletalAnimModelEntity);
			macDemoPhysics3SkeletalAnimModelEntity		= 0;
		}

		macDemoCameras[0] = MacDemoCameraEntity::create("MacDemoCameraEntity");
		{
			PerspectiveCameraComponent &camera = macDemoCameras[0]->getCamera();
			camera.setViewport(Vector4(0, 0, 1, 1));
			camera.setProjection(Math::ONE_PI*45/180, 960.0f/640.0f, 0.1, 3000);
			camera.setTargetLayer(0x01);
			camera.setClearFlags(CameraComponent::CLEAR_COLOR | CameraComponent::CLEAR_DEPTH);
		}
		macDemoCameras[0]->initLookAt(cameraPosition, Vector3::ZERO, Vector3::UNIT_Y);
		macDemoCameras[0]->construct();

		for(int i=0; i<macDemoPlaneEntities.length(); i++)
		{
			String name;
			name.format("macDemoPlaneEntities%d", i);
			MacDemoPlaneEntity *ent = MacDemoPlaneEntity::create(name);
			macDemoPlaneEntities[i] = ent;

			int idx = i - macDemoPlaneEntities.length() / 2;
			macDemoPlaneEntities[i]->initTranslateScale(idx*20, 0, 0, 1.0f);
			macDemoPlaneEntities[i]->construct();
		}
		 
		macDemoSkySphere = MacDemoSkySphereEntity::create("MacDemoSkySphereEntity");
		macDemoSkySphere->construct();

		{
			String name;
			name.format("MacDemoAudioSourceEntity");
			macDemoAudioSourceEntity = MacDemoAudioSourceEntity::create(name);
			macDemoAudioSourceEntity->initTranslate(10, 0, 0);
			macDemoAudioSourceEntity->construct();
		}

		{
			String name;
			name.format("MacDemoBGMEntity");
			macDemoBGMEntity = MacDemoBGMEntity::create(name);
			macDemoBGMEntity->initTranslate(10, 0, 0);
			macDemoBGMEntity->construct();
		}

		{
			String name;

			name.format("MacDemoLevelEntity");
			macDemoLevelEntity = MacDemoLevelEntity::create(name);
			macDemoLevelEntity->initTranslate(0, 0, 0);
			macDemoLevelEntity->construct();
		}

		{
			String name;
			name.format("MacDemoAudioListenerEntity");
			macDemoAudioListenerEntity = MacDemoAudioListenerEntity::create(name);
			macDemoAudioListenerEntity->initTranslate(10, 0, 0);
			macDemoAudioListenerEntity->construct();
		}

		{
			String name;
			name.format("MacDemoBillBoardEntity");
			macDemoBillBoardEntity = MacDemoBillBoardEntity::create(name);
			macDemoBillBoardEntity->initTranslateScale(3, 0, 0, 1);
			macDemoBillBoardEntity->construct();
		}

		{
			String name;
			name.format("MacDemoCubeEntity");
			macDemoCubeEntity = MacDemoCubeEntity::create(name);
			macDemoCubeEntity->initTranslateScale(0, 0, 0, 1);
			macDemoCubeEntity->construct();
		}

		{
			String name;
			name.format("MacDemoDiffuseMapCubeEntity");
			macDemoDiffuseMapCubeEntity = MacDemoDiffuseMapCubeEntity::create(name);
			macDemoDiffuseMapCubeEntity->initTranslateScale(1, 0, 0, 1);
			macDemoDiffuseMapCubeEntity->construct();
		}

		{
			String name;
			name.format("MacDemoDiffuseMapSpecularMapCubeEntity");
			macDemoDiffuseMapSpecularMapCubeEntity = MacDemoDiffuseMapSpecularMapCubeEntity::create(name);
			macDemoDiffuseMapSpecularMapCubeEntity->initTranslateScale(2, 0, 0, 1);
			macDemoDiffuseMapSpecularMapCubeEntity->construct();
		}

		{
			String name;
			name.format("MacDemoParticleEmitterEntity");
			macDemoParticleEmitterEntity = MacDemoParticleEmitterEntity::create(name);
			macDemoParticleEmitterEntity->initTranslateScale(3, 0, 0, 1);
			macDemoParticleEmitterEntity->construct();
		}

		{
			String name;
			name.format("MacDemoPhysics3SkeletalAnimModelEntity");
			macDemoPhysics3SkeletalAnimModelEntity = MacDemoPhysics3SkeletalAnimModelEntity::create(name);
			macDemoPhysics3SkeletalAnimModelEntity->initTranslateRotZXYScale(0, 20, 0, 0.0f, Math::ONE_PI*3.0/4.0, 0.0f, 1.0);
			macDemoPhysics3SkeletalAnimModelEntity->construct();
		}

		state = MAIN;

		break;

	case CHECKING_RAWASSETS:
#ifdef ENABLE_RESOURCE_IMPORT
		/////////////////////////////////////////////////////////////////////////////////////////
		if(!ResourceImport::Factory::instance().isCheckingRawAssets())
		{
			const Vector<System::File> &newResourceFiles    = ResourceImport::Factory::instance().getNewReourceFiles();
			const Vector<System::File> &reloadResourceFiles = ResourceImport::Factory::instance().getReloadResourceFiles();
			const Vector<System::File> &deleteResourceFiles = ResourceImport::Factory::instance().getDeleteReourceFiles();

			ResourceAccess::Factory::instance().beginUpdateResources(newResourceFiles, reloadResourceFiles, deleteResourceFiles);

			state = UPDATING_ASSETS;
		}
		else
		{
			debug("CheckingRawAssets");
		}
#endif
		break;

	case UPDATING_ASSETS:
#ifdef ENABLE_RESOURCE_IMPORT
		/////////////////////////////////////////////////////////////////////////////////////////
		if(!ResourceAccess::Factory::instance().isUpdatingResources())
		{
			state = VALIDATE_ENTITIES;
		}
		else
		{
			debug("UpdatingAssets");
		}
#endif
		break;

	case VALIDATE_ENTITIES:

		state = MAIN;

		break;

	case MAIN:

		/////////////////////////////////////////////////////////////////////////////////////////
		updateCamera();

		break;
	};
}

//	called when about to paused
void MacDemoScene::onPause()
{
}

//	called when about to resume
void MacDemoScene::onResume()
{
}

//	called while transitioning returning false stops transition mode
bool MacDemoScene::onTransition(TransitionMode mode)
{
	return false;
}

void MacDemoScene::touchpadEvent(const Input::TouchpadEvent &evt)
{
	switch(state)
	{
	case START:
		break;

	case LOAD:
		break;

	case CHECKING_RAWASSETS:
		break;

	case UPDATING_ASSETS:
		break;

	case VALIDATE_ENTITIES:
		break;

	case MAIN:
		switch(evt.event)
		{
		case Input::EVENT_MOUSE_UP:

			mode = 0;
			debug("Mouse Up %d %f %f", evt.fingerID, evt.position.X(), evt.position.Y());

			break;

		case Input::EVENT_MOUSE_DOWN:

			if(evt.fingerID==0)
			{
				mode = 1;
				mouseDownPosition	= evt.position;
				oldPhi				= phi;
				oldTheta			= theta;
				oldRadius			= radius;
			}
			else if(evt.fingerID==1)
			{
				mode = 2;
				mouseDownPosition	= evt.position;
				oldPhi				= phi;
				oldTheta			= theta;
				oldRadius			= radius;
			}

			// debug("Mouse Down %d %f %f", evt.fingerID, evt.position.X(), evt.position.Y());

			break;

		case Input::EVENT_MOUSE_MOVE:

			if(mode==1)
			{
				Vector2 dpos = (evt.position - mouseDownPosition);

				theta		= oldTheta	+ dpos.X() * Math::ONE_PI			/ (Stage::getScreenWidth() /2);
				phi			= oldPhi	+ dpos.Y() * Math::HALF_PI*70/90	/ (Stage::getScreenHeight()/2);
				if(phi>Math::HALF_PI*70/90)
				{
					phi = Math::HALF_PI*70/90;
				}
				else if(phi<-Math::HALF_PI*70/90)
				{
					phi = -Math::HALF_PI*70/90;
				}
			}

			// debug("Mouse Move %f %f", evt.position.X(), evt.position.Y());
			break;
		}
		break;
	};
}

void MacDemoScene::keypadEvent(const Input::GamepadEvent &evt)
{
	switch(state)
	{
	case START:
		if(evt.event==Input::EVENT_GAMEPAD_KEY_UP)
		{
		}
		else if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
		{
			if(evt.keyCode==Input::KEY_SPECIAL0)
			{
#ifdef ENABLE_RESOURCE_IMPORT
				ResourceImport::Factory::instance().beginCheckRawAssets();
				state = CHECKING_RAWASSETS;
#endif
			}
		}
		break;

	case LOAD:
		if(evt.event==Input::EVENT_GAMEPAD_KEY_UP)
		{
		}
		else if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
		{
		}
		break;

	case CHECKING_RAWASSETS:
		if(evt.event==Input::EVENT_GAMEPAD_KEY_UP)
		{
		}
		else if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
		{
		}
		break;

	case UPDATING_ASSETS:
		if(evt.event==Input::EVENT_GAMEPAD_KEY_UP)
		{
		}
		else if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
		{
		}
		break;

	case VALIDATE_ENTITIES:
		break;

	case MAIN:
		if(evt.event==Input::EVENT_GAMEPAD_KEY_UP)
		{
			if(macDemoCameras[0])
			{
				if(evt.keyCode==Input::KEYPAD0_UP)
				{
					velocity.Z() = 0;
				}
				if(evt.keyCode==Input::KEYPAD0_DOWN)
				{
					velocity.Z() = 0;
				}
				if(evt.keyCode==Input::KEYPAD0_LEFT)
				{
					velocity.X() = 0;
				}
				if(evt.keyCode==Input::KEYPAD0_RIGHT)
				{
					velocity.X() = 0;
				}
			}
		}
		else if(evt.event==Input::EVENT_GAMEPAD_KEY_DOWN)
		{	
			if(macDemoCameras[0])
			{
				if(evt.keyCode==Input::KEYPAD0_UP)
				{
					velocity.Z() = 5;
				}
				if(evt.keyCode==Input::KEYPAD0_DOWN)
				{
					velocity.Z() = -5;
				}
				if(evt.keyCode==Input::KEYPAD0_LEFT)
				{
					velocity.X() = -5;
				}
				if(evt.keyCode==Input::KEYPAD0_RIGHT)
				{
					velocity.X() = 5;
				}
			}

			if(evt.keyCode==Input::KEYPAD0_SELECT)
			{
				Scene::transit("SimpleGameTest");
			}
			if(evt.keyCode==Input::KEY_SPECIAL1)
			{
				state = LOAD;
			}
		}
		break;
	};
}

void MacDemoScene::acceleratorEvent(const Input::AcceleratorEvent &evt)
{
	switch(state)
	{
	case START:
		break;

	case LOAD:
		break;

	case CHECKING_RAWASSETS:
		break;

	case UPDATING_ASSETS:
		break;

	case VALIDATE_ENTITIES:
		break;

	case MAIN:
		break;
	};
}

void MacDemoScene::updateCamera()
{
	Vector3 cameraLookAt;

	cameraLookAt.X() = 10.0f*Math::Cos(phi)*Math::Cos(theta);
	cameraLookAt.Y() = 10.0f*Math::Sin(phi);
	cameraLookAt.Z() = 10.0f*Math::Cos(phi)*Math::Sin(theta);

	if(macDemoCameras[0])
	{
		float time = ((float)Stage::elapsed()) / 1000.0f;
		Vector3 v = -macDemoCameras[0]->getGlobalZAxis() * velocity.Z() + macDemoCameras[0]->getGlobalXAxis() * velocity.X();
		cameraPosition += v * time;

		macDemoCameras[0]->initLookAt(cameraPosition, cameraPosition+cameraLookAt, Vector3::UNIT_Y);

		if(macDemoAudioListenerEntity)
			macDemoAudioListenerEntity->setLocalTransform(macDemoCameras[0]->getGlobalTransform());
	}
}